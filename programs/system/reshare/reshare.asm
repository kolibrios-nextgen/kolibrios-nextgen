; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

format binary as ""
use32
org     0
db      'MENUET01'    ; signature
dd      1             ; header version
dd      start         ; entry point
dd      _image_end    ; end of image
dd      _memory       ; required memory size
dd      _stacktop     ; address of stack top
dd      0             ; buffer for command line arguments
dd      0             ; buffer for path

__DEBUG__       = 1
__DEBUG_LEVEL__ = DBG_ERR
DBG_ALL       = 0  ; all messages
DBG_INFO      = 1  ; info and errors
DBG_ERR       = 2  ; only errors

SHM_CREATE      = 0x08
SHM_READ        = 0x00
SHM_WRITE       = 0x01
SHM_OPEN        = 0x00
SHM_OPEN_ALWAYS = 0x04

include 'macros.inc'
include 'KOSfuncs.inc'
purge   mov, add, sub ; ?
include 'debug-fdo.inc'
include 'proc32.inc'
include 'dll.inc'
include 'string.inc'
include 'if.inc'
include 'libimg.inc'


proc replace_2cols stdcall uses edi, imgsrc, imgsize, color_old_1, color_new_1, color_old_2, color_new_2
    mov     edx, [imgsize]
    add     edx, [imgsrc]
    mov     edi, [imgsrc]
    .while edi < edx
        mov eax, [edi]
        .if eax = [color_old_1]
            mov eax, [color_new_1]
            mov [edi], eax
        .elseif eax = [color_old_2]
            mov eax, [color_new_2]
            mov [edi], eax
        .endif
        add edi, 4
    .endw
    ret
endp


align 4
start:
    mcall   SF_SYS_MISC, SSF_HEAP_INIT

    stdcall dll.Load, @imports

    DEBUGF  DBG_INFO, "@reshare: loading resources..\n"

    invoke  img.from_file, icons32_path
    .if eax <> 0
        mov     [icons32_image], eax
        ; DEBUGF  DBG_INFO, "@reshare: icons32_height = %u, icons32_width = %u ", [eax + Image.Height], [eax + Image.Width]
        mov     eax, [eax + Image.Height]
        shl     eax, 7 ; *32*4
        mov     [size32], eax
        ; DEBUGF  DBG_INFO, "size32 = %u\n", [size32]
    .else
        DEBUGF  DBG_ERR, "@reshare: error, icons32 not found in %s\n", icons32_path
    .endif
    
    invoke  img.from_file, icons16_path
    .if eax <> 0
        mov     [icons16_image], eax
        ; DEBUGF  DBG_INFO, "@reshare: icons16_height = %u, icons16_width = %u ", [eax + Image.Height], [eax + Image.Width]
        mov     eax, [eax + Image.Height]
        imul    eax, 18*4
        mov     [size16], eax
        ; DEBUGF  DBG_INFO, "size16 = %u\n", [size16]
    .else
        DEBUGF  DBG_ERR, "@reshare: error, icons16 not found in %s\n", icons16_path
    .endif
    ; check if this is second instance of app. if so, run gui. else daemon mode
    mcall   SF_THREAD_INFO, thread_info, -1
    stdcall string.copy, thread_info + 10, thread_name
    stdcall string.to_lower_case, thread_name
    xor     edx, edx ; instance count
    xor     esi, esi
    .while esi < 256
        mcall   SF_THREAD_INFO, thread_info, esi
        stdcall string.to_lower_case, thread_info + 10
        stdcall string.cmp, thread_info + 10, thread_name, -1
        .if eax = 0
            inc     edx
            cmp     edx, 2
            jae     start_gui
        .endif
        inc     esi
    .endw
    jmp     daemon_mode

.exit:
        mcall   SF_TERMINATE_PROCESS


WINW = 775
WINH = 660
WINX = 80
WINY = 50
PAD  = 10
BTNW = 100
BTNH = 24
RESY = PAD + 30 + BTNH + BTNH
FONT_TYPE = 0x90

start_gui:

.event_loop:
    mcall   SF_WAIT_EVENT

    cmp     eax, EV_REDRAW
    je      .event_redraw

    cmp     eax, EV_KEY
    je      .event_key

    cmp     eax, EV_BUTTON
    je      .event_button

    jmp     .event_default

.event_redraw:
    mcall   SF_STYLE_SETTINGS, SSF_GET_COLORS, sc, sizeof.system_colors

    mcall   SF_REDRAW, SSF_BEGIN_DRAW
    mcall   SF_STYLE_SETTINGS, SSF_GET_SKIN_HEIGHT
    mov     ecx, WINY
    shl     ecx, 16
    add     ecx, WINH + 4
    add     ecx, eax ; ecx = <WINY, WINH + 4 + GetSkinHeight()>
    xor     eax, eax ; SF_CREATE_WINDOW
    mov     ebx, (WINX shl 16) + WINW + 9
    mov     edx, (0x74 shl 24) or 0;
    xor     esi, esi ; flags = 0
    mov     edi, window_title
    mcall
    mcall   SF_REDRAW, SSF_END_DRAW

    mcall   SF_DRAW_RECT, <0, WINW>, <0, RESY-PAD-1>, [sc.work] ; top bg
    mcall   SF_DRAW_RECT, <0, WINW>, <RESY-PAD-1, 1>, [sc.work_graph]

    mov     ecx, FONT_TYPE shl 24
    add     ecx, [sc.work_text]
    mcall   SF_DRAW_TEXT, <PAD, PAD>, , window_top_text

    stdcall draw_tabs

    jmp     .event_default

.event_key:
    mcall   SF_GET_KEY
    shr     eax, 16
    .if al = 1 ; ESC
        mcall   SF_TERMINATE_PROCESS
    .elseif al = 15 ; TAB
        shl     [active_tab], 1 ; * 2
        .if [active_tab] > MASK_ACTIVE_CHECKBOX
            mov     [active_tab], 1
        .endif
        stdcall draw_tabs
    .endif
    jmp     .event_default

.event_button:
    mcall   SF_GET_BUTTON
    shr     eax, 8
    .if eax = 1
        mcall   SF_TERMINATE_PROCESS
    .else
        sub     eax, 10
        mov     [active_tab], eax
        stdcall draw_tabs
    .endif
    jmp     .event_default

.event_default:
    jmp     .event_loop


MASK_ACTIVE_ICONS32 = 1
MASK_ACTIVE_ICONS16 = 2
MASK_ACTIVE_ICONS16W = 4
MASK_ACTIVE_CHECKBOX = 8
TABX = (WINW-BTNW-PAD-BTNW-PAD-BTNW-PAD-BTNW)/2

proc draw_tabs stdcall
    mov     eax, [active_tab]
    and     eax, MASK_ACTIVE_ICONS32
    stdcall draw_flat_button, TABX, PAD + 30, shared_i32_name,  10 + MASK_ACTIVE_ICONS32, eax
    mov     eax, [active_tab]
    and     eax, MASK_ACTIVE_ICONS16
    stdcall draw_flat_button, (PAD + BTNW)*1 + TABX, PAD + 30, shared_i16_name,  10 + MASK_ACTIVE_ICONS16, eax
    mov     eax, [active_tab]
    and     eax, MASK_ACTIVE_ICONS16W
    stdcall draw_flat_button, (PAD + BTNW)*2 + TABX, PAD + 30, shared_i16w_name, 10 + MASK_ACTIVE_ICONS16W, eax
    mov     eax, [active_tab]
    and     eax, MASK_ACTIVE_CHECKBOX
    stdcall draw_flat_button, (PAD + BTNW)*3 + TABX, PAD + 30, shared_chbox_name, 10 + MASK_ACTIVE_CHECKBOX, eax
    
    stdcall draw_tab_icons32
    ret
endp


proc draw_tab_icons32 stdcall uses ebx esi edi
locals
    x       dd PAD
    y       dd 0
    iconimg dd ?
    iconh   dd ?
    iconw   dd ?
    icon_h_div_w  dd ?
    num_str rb 16
endl
    mcall   SF_DRAW_RECT, <0, WINW>, <RESY-PAD, WINH-RESY+PAD>, [sc.work]
    mov eax, [active_tab]
    .if eax = MASK_ACTIVE_ICONS32
        cmp     [icons32_image], 0
        jz      .exit
        mov     ebx, [icons32_image]
        mov     eax, [ebx + Image.Data]
        mov     [iconimg], eax
        mov     [iconw], 32
        mov     eax, [ebx + Image.Height]
        mov     [iconh], eax
        
    .elseif eax = MASK_ACTIVE_ICONS16
        cmp     [icons16_image], 0
        jz      .exit
        mov     ebx, [icons16_image]
        mov     eax, [ebx + Image.Data]
        mov     [iconimg], eax
        mov     [iconw], 18
        mov     eax, [ebx + Image.Height]
        mov     [iconh], eax

    .elseif eax = MASK_ACTIVE_ICONS16W
        cmp     [icons16_image], 0
        jz      .exit
        mcall   SF_SYS_MISC, SSF_MEM_OPEN, shared_i16w_name, 0, SHM_OPEN + SHM_READ
        mov     [iconimg], eax
        mov     [iconw], 18
        mov     ebx, [icons16_image]
        mov     eax, [ebx + Image.Height]
        mov     [iconh], eax

    .else
        mov     ebx, checkbox_flag
        mov     ecx, CHBOX_WIDTH
        shl     ecx, 16
        add     ecx, CHBOX_HEIGHT
        mov     edx, (WINW - CHBOX_WIDTH)/2
        shl     edx, 16
        add     edx, (WINH - RESY - CHBOX_HEIGHT)/2 + RESY
        mcall   SF_PUT_IMAGE
        ret
    .endif
    xor     edx, edx
    mov     eax, [iconh]
    div     [iconw]
    mov     [icon_h_div_w], eax

    xor     ecx, ecx
.for_icons:
    cmp     ecx, [icon_h_div_w]
    jae     .end_for_icons
    push    ecx
    ; PutPaletteImage(iconw*iconw*4*i + iconimg, iconw, iconw, 50-iconw/2+x, y+RESY, 32, 0);
    mov     ebx, [iconw]
    imul    ebx, ebx
    shl     ebx, 2 ; *4
    imul    ebx, ecx
    add     ebx, [iconimg]
    mov     ecx, [iconw]
    shl     ecx, 16
    add     ecx, [iconw]

    ; X = (50-iconw)/2+x, Y = y + RESY
    mov     edx, 50
    sub     edx, [iconw]
    shr     edx, 1 ; /2
    add     edx, [x]
    shl     edx, 16
    add     edx, [y]
    add     edx, RESY

    mov     esi, 32
    xor     edi, edi
    push    ebp
    xor     ebp, ebp
    mcall   SF_PUT_IMAGE_EXT
    pop     ebp
    
    ; WriteText(-strlen(itoa(i))*8+50/2+x, y+RESY+iconw+5, 0x90, sc.line, itoa(i));
    mov     ecx, [esp] ; get saved ecx (counter) from the stack
    xor     esi, esi ; counter
    mov     eax, ecx ; number in eax
    lea     edi, [num_str] ; buffer in edi
    xor     ecx, ecx
    push    ecx
    mov     ecx, 10
@@:
    xor     edx, edx
    div     ecx
    add     edx, '0'
    push    edx
    inc     esi
    test    eax, eax
    jnz     @b
@@:
    pop     eax
    stosb
    test    eax, eax
    jnz     @b

    shl     esi, 3 ; *8
    mov     ebx, 50
    sub     ebx, esi
    shr     ebx, 1 ; /2
    add     ebx, [x]
    shl     ebx, 16
    add     ebx, [y]
    add     ebx, [iconw]
    add     ebx, RESY + 5
    
    mov     ecx, 0x90 shl 24
    add     ecx, [sc.work_graph]
    lea     edx, [num_str]
    mcall   SF_DRAW_TEXT

    add     [x], 50
    .if [x] > WINW - 50
        mov     [x], PAD
        mov     eax, [iconw]
        add     [y], eax
        add     [y], 30
    .endif

    pop     ecx
    inc     ecx
    jmp     .for_icons
.end_for_icons:

.exit:
    ret
endp


BTN_HIDE = 0x40000000
proc draw_flat_button stdcall uses ebx esi, _x, _y, _text, _id, _active
    mov     edx, [sc.work_light]
    .if [_active] <> 0
        mov     edx, [sc.work_button]
    .endif
    mov     ebx, [_x]
    shl     ebx, 16
    add     ebx, BTNW
    mov     ecx, [_y]
    shl     ecx, 16
    add     ecx, BTNH + 1
    mcall   SF_DRAW_RECT

    mov     edx, [sc.work_text]
    .if [_active] <> 0
        mov     edx, [sc.work_button_text]
    .endif
    mov     ebx, [_x]
    add     ebx, BTNW/2
    stdcall string.length, [_text]
    shl     eax, 2 ; *4
    sub     ebx, eax ; ebx =_x + (BTNW - strlen(_text)*8)/2 = _x + BTNW/2 - strlen(_text)*4
    shl     ebx, 16
    add     ebx, [_y]
    add     ebx, 6
    mov     ecx, 0x90 shl 24
    add     ecx, edx
    mov     edx, [_text]
    mcall   SF_DRAW_TEXT

    mcall   SF_PUT_PIXEL, [_x], [_y], [sc.work] ; PutPixel(_x,_y,sc.work);
    add     ecx, BTNH
    mcall   , [_x], , ; PutPixel(_x,_y+BTNH,EDX);
    add     ebx, BTNW-1
    mcall   , , [_y], ; PutPixel(_x+BTNW-1,_y,EDX);
    add     ecx, BTNH
    mcall   ; PutPixel(_x+BTNW-1,_y+BTNH,EDX);

    ; DefineHiddenButton(_x, _y, BTNW-1, BTNH, _id):
    mov     eax, SF_DEFINE_BUTTON
    mov     ebx, [_x]
    shl     ebx, 16
    add     ebx, BTNW-1
    mov     ecx, [_y]
    shl     ecx, 16
    add     ecx, BTNH
    mov     edx, [_id]
    or      edx, BTN_HIDE
    xor     esi, esi
    mcall

    ret
endp


daemon_mode:
    DEBUGF  DBG_INFO, "@reshare: started in daemon mode\n"

    mcall   SF_SYS_MISC, SSF_MEM_OPEN, shared_chbox_name, CHBOX_SIZE, SHM_CREATE + SHM_WRITE
    mov     esi, checkbox_flag
    mov     edi, eax
    mov     ecx, CHBOX_SIZE
    cld
    rep     movsb

    .if [icons32_image] <> 0
        mcall   SF_SYS_MISC, SSF_MEM_OPEN, shared_i32_name, [size32], SHM_CREATE + SHM_WRITE
        mov     ebx, [icons32_image]
        mov     esi, [ebx + Image.Data]
        mov     edi, eax
        mov     ecx, [size32]
        shr     ecx, 2 ; / 4 to get size in dwords
        cld
        rep     movsd
        invoke  img.destroy, [icons32_image]
    ; .else
    ;     DEBUGF  DBG_ERR, "Daemon mode: no icons32 !\n"
    .endif

    .if [icons16_image] <> 0
        mcall   SF_SYS_MISC, SSF_MEM_OPEN, shared_i16_name, [size16], SHM_CREATE + SHM_WRITE
        mov     ebx, [icons16_image]
        mov     esi, [ebx + Image.Data]
        mov     edi, eax
        mov     ecx, [size16]
        shr     ecx, 2 ; / 4 to get size in dwords
        cld
        rep     movsd

        mcall   SF_SYS_MISC, SSF_MEM_OPEN, shared_i16w_name, [size16], SHM_CREATE + SHM_WRITE
        mov     [shared_i16w], eax
    ; .else
    ;     DEBUGF  DBG_ERR, "Daemon mode: no icons16 !\n"
    .endif
    
    mcall   SF_SET_EVENTS_MASK, 10000b ; set event mask EVM_DESKTOPBG
.event_loop:
    push    [sc.work]
    mcall	SF_STYLE_SETTINGS, SSF_GET_COLORS, sc, sizeof.system_colors
    pop     eax
    .if eax <> [sc.work]
        .if [icons16_image] <> 0
            mov     ebx, [icons16_image]
            mov     esi, [ebx + Image.Data]
            mov     edi, [shared_i16w]
            mov     ecx, [size16]
            shr     ecx, 2 ; / 4 to get size in dwords
            cld
            rep     movsd
            shl     ebx, 2 ; get size in bytes
            stdcall replace_2cols, [shared_i16w], [size16], 0xffFFFfff, [sc.work], 0xffCACBD6, [sc.work_dark]
        .endif
    .endif
    mcall   SF_WAIT_EVENT
    cmp     eax, 5 ; redraw background event
    je      .event_loop

.exit:
    mcall   SF_TERMINATE_PROCESS


; data:
include_debug_strings

@imports:
        library img, "libimg.obj"
        import  img, img.destroy, "img_destroy", \
                img.from_file,    "img_from_file"

icons32_path    db "/SYS/ICONS32.PNG", 0
icons16_path    db "/SYS/ICONS16.PNG", 0
; pointers to Image structures
icons32_image   dd 0
icons16_image   dd 0
; sizes of icons image data in bytes
size32          dd 0
size16          dd 0

shared_i32_name db "ICONS32", 0
shared_i16_name db "ICONS18", 0
shared_i16w     dd 0
shared_i16w_name db "ICONS18W", 0
include         'chbox.inc'
shared_chbox_name db "CHECKBOX", 0

window_title    db "@RESHARE - A service that provides shared resources", 0
window_top_text db "Each tab name corresponds to memory name that can be accessed by sysfunc 68.22. Now available:", 0

active_tab      dd MASK_ACTIVE_ICONS32

sc              system_colors

align 16
_image_end:

thread_info     process_information
thread_name     rb 16

; cmdline rb 255

; reserve for stack:
        rb      4096
align 16
_stacktop:
_memory:





