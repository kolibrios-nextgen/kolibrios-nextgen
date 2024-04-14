;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                              ;;
;; Copyright (C) KolibriOS team 2022-2023. All rights reserved. ;;
;; Copyright (C) KolibriOS-NG team 2024. All rights reserved.   ;;
;; Distributed under terms of the GNU General Public License    ;;
;;                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

; constants for formatted debug
__DEBUG__       = 1             ; 0 - disable debug output / 1 - enable debug output
__DEBUG_LEVEL__ = DBG_INFO       ; set the debug level
DBG_ALL       = 0  ; all messages
DBG_INFO      = 1  ; info and errors
DBG_ERR       = 2  ; only errors

include '../../macros.inc'
purge   mov, add, sub ; ?
include '../../debug-fdo.inc'
include '../../proc32.inc'
include '../../dll.inc'

include '../../develop/libraries/libs-dev/libimg/libimg.inc'

;//<= imgsrc, imgsize, color_old_1, color_new_1, color_old_2, color_new_2
;inline fastcall replace_2cols(EDI, EDX, ESI, ECX, EBX, EAX) 
;{
;    EDX += EDI; //imgsrc + imgsize;
;    WHILE (EDI < EDX) {
;        IF (DSDWORD[EDI]==ESI) DSDWORD[EDI] = ECX;
;        ELSE IF (DSDWORD[EDI]==EBX) DSDWORD[EDI] = EAX;
;        EDI += 4;
;    }
;
;}

proc replace_2cols stdcall uses edi, imgsrc, imgsize, color_old_1, color_new_1, color_old_2, color_new_2
        mov     edx, [imgsize]
        add     edx, [imgsrc]
        mov     edi, [imgsrc]
.while:
        cmp     edi, edx
        jae     .end

        mov     eax, [edi]

        cmp     eax, [color_old_1]
        jne     @f
        mov     eax, [color_new_1]
        mov     [edi], eax
        jmp     .cont
@@:
        cmp     eax, [color_old_2]
        jne     .cont
        mov     eax, [color_new_2]
        mov     [edi], eax
.cont:
        add     edi, 4
        jmp     .while
.end:

        ret
endp


align 4
start:
        mcall   68, 11 ; init dynamic memory

        stdcall dll.Load, @imports

        DEBUGF  DBG_INFO, "@reshare: privet 2 !\n"

        invoke  img.from_file, icons32_path
        test    eax, eax
        jz      .icons32_not_found
        mov     [icons32_image], eax
        DEBUGF  DBG_INFO, "@reshare: icons32_height = %u, icons32_width = %u\n", [eax + Image.Height], [eax + Image.Width]
        mov     eax, [eax + Image.Height]
        shl     eax, 7 ; *32*4
        mov     [size32], eax
        DEBUGF  DBG_INFO, "size32 = %u\n", [size32]
        jmp     @f
        
.icons32_not_found:
        DEBUGF  DBG_ERR, "@reshare: error, icons32 not found by %s\n", icons32_path
@@:
        invoke  img.from_file, icons16_path
        test    eax, eax
        jz      .icons16_not_found
        mov     [icons16_image], eax
        DEBUGF  DBG_INFO, "@reshare: icons16_height = %u, icons16_width = %u\n", [eax + Image.Height], [eax + Image.Width]
        mov     eax, [eax + Image.Height]
        imul    eax, 18*4
        mov     [size16], eax
        DEBUGF  DBG_INFO, "size16 = %u\n", [size16]
        jmp     @f
.icons16_not_found:
        DEBUGF  DBG_ERR, "@reshare: error, icons16 not found by %s\n", icons16_path
@@:
        jmp     daemon_mode

.exit:
        mov     eax, -1
        mcall


daemon_mode:
        DEBUGF  DBG_INFO, "@reshare: start sharing\n"

        mov     edi, [size32]
        mcall   68, 22, shared_i32_name, edi,  0x08 + 0x01 ;SHM_CREATE + SHM_WRITE
        mov     [shared_i32], eax
        mov     ebx, [icons32_image]
        mov     esi, [ebx + Image.Data]
        mov     edi, eax
        mov     ecx, [size32]
        shr     ecx, 2 ; / 4 to get size in dwords
        cld
        rep     movsd

        mov     edi, [size16]
        mcall   68, 22, shared_i16_name, edi,  0x08 + 0x01 ;SHM_CREATE + SHM_WRITE
        mov     [shared_i16], eax
        mov     ebx, [icons16_image]
        mov     esi, [ebx + Image.Data]
        mov     edi, eax
        mov     ecx, [size16]
        shr     ecx, 2 ; / 4 to get size in dwords
        cld
        rep     movsd

        mov     edi, [size16]
        mcall   68, 22, shared_i16w_name, edi,  0x08 + 0x01 ;SHM_CREATE + SHM_WRITE
        mov     [shared_i16w], eax

        DEBUGF  DBG_INFO, "@reshare: shared\n"
        
        mcall 40, 10000b ; set event mask EVM_DESKTOPBG
.event_loop:
        push    [sc.work]
        mcall	48, 3, sc, sizeof.system_colors
        pop     eax
        cmp     eax, [sc.work]
        je      @f
        mov     ebx, [icons16_image]
        mov     esi, [ebx + Image.Data]
        mov     edi, [shared_i16w]
        mov     ecx, [size16]
        shr     ecx, 2 ; / 4 to get size in dwords
        cld
        rep     movsd
        shl     ebx, 2 ; get size in bytes
        stdcall replace_2cols, [shared_i16w], [size16], 0xffFFFfff, [sc.work], 0xffCACBD6, [sc.work_dark]
@@:
        mcall   10
        cmp     eax, 5
        je      .event_loop

.exit:
        mov     eax, -1
        mcall


; data:
include_debug_strings

@imports:
        library img, "libimg.obj"
        import  img, img.destroy, "img_destroy", \
		img.from_file,    "img_from_file"

icons32_path    db "/SYS/ICONS32.PNG", 0
icons16_path    db "/SYS/ICONS16.PNG", 0
; pointers to Image structures
icons32_image   dd ?
icons16_image   dd ?
; sizes of icons image data in bytes
size32          dd ?
size16          dd ?

shared_i32      dd ?
shared_i32_name db "ICONS32", 0
shared_i16      dd ?
shared_i16_name db "ICONS18", 0
shared_i16w     dd ?
shared_i16w_name db "ICONS18W", 0
shared_chbox    dd ?

sc              system_colors

align 16
_image_end:

; cmdline rb 255

; reserve for stack:
        rb      4096
align 16
_stacktop:
_memory:





