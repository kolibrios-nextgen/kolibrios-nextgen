; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; AСlock - Analog clock (with arrow)

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

format binary as ""
use32
org 0

;----------------- Programm header ------------------;

db      'MENUET01'    ; signature
dd      1             ; header version
dd      start         ; entry point
dd      _image_end    ; end of image
dd      _memory       ; required memory size
dd      _stacktop     ; address of stack top
dd      0             ; buffer for command line arguments
dd      0             ; buffer for path

;-------------------- Includes ----------------------;

; System
include 'kos_api.inc'

; Internal
include 'strlen.inc'
include 'str2dwrd.inc'
include 'strtok.inc'
include 'cmdline.inc'
include 'strtok.inc'
include 'adjstwnd.inc'
;%include 'draw.inc'    ; TODO: Rewrite to FASM

;-------------------- Constants ---------------------;

; Default window position/dimensions (work area)

DEFAULT_XPOS    = -20
DEFAULT_YPOS    = 20
DEFAULT_WIDTH   = 110
DEFAULT_HEIGHT  = 110

; Minimal size (horizontal and vertical) of work area

MIN_WIDTH       = 100
MIN_HEIGHT      = 100

;---------------------- Code ------------------------;

; Entry point
start:
        ; Get default colors
        mcall   SF_STYLE_SETTINGS,
                SSF_GET_COLORS,
                win_colors,
                sizeof.KOS_SYS_COLORS_S

        call    parse_command_line

        ; Check minimal window dimensions
        cmp     dword [win_w], MIN_WIDTH
        jae     .width_ok
        mov     dword [win_w], MIN_WIDTH

.width_ok:
        cmp     dword [win_h],MIN_HEIGHT
        jae     .height_ok
        mov     dword [win_h],MIN_HEIGHT

.height_ok:
        ; Adjust window dimensions
        mov     eax, ADJSTWND_TYPE_SKINNED
        mov     ebx, [win_x_pos]
        mov     ecx, [win_y_pos]
        mov     edx, [win_w]
        mov     esi, [win_h]
        call    adjust_window_dimensions
        mov     [win_x_pos], ebx
        mov     [win_y_pos], ecx
        mov     [win_w], edx
        mov     [win_h], esi

        call	draw_window
.msg_pump:

        ; Wait up to a second for next event
        mcall   SF_WAIT_EVENT_TIMEOUT, 100
        test    eax, eax
        jne     .event_occured
        call    draw_clock

.event_occured:
        cmp     eax, KOS_EV_REDRAW
        je      .redraw
        cmp     eax, KOS_EV_KEY
        je      .key
        cmp      eax, KOS_EV_BUTTON
        je      .button
        jmp     .msg_pump

.redraw:
        call    draw_window
        jmp     .msg_pump
.key:
        mcall   SF_GET_KEY
	jmp     .msg_pump
.button:
        xor     eax, eax
        dec     eax
        ; eax = SF_TERMINATE_PROCESS (-1)
        mcall

; Define and draw window
align 4
draw_window:
        pusha

        ; Start window redraw
        mcall	SF_REDRAW, SSF_BEGIN_DRAW

        ; Create window
        xor     eax, eax ; SF_CREATE_WINDOW
        mov     ebx, [win_x_pos]
        shl     ebx, 16
        or      ebx, [win_w]
        mov     ecx, [win_y_pos]
        shl     ecx, 16
        or      ecx, [win_h]
        mov     edx, [win_colors+KOS_SYS_COLORS_S.work]
        or      edx, 0x53000000 ; FIXME: Magic number ???
        mov     edi, label
        mcall

        call    draw_clock

        ; End window redraw
        mcall   SF_REDRAW, SSF_END_DRAW
        popa
        ret

;----------------- Initialized data -----------------;

; Window position and dimensions.
; dimensions are for work area only.
win_x_pos       dd DEFAULT_XPOS
win_y_pos       dd DEFAULT_YPOS
win_w           dd DEFAULT_WIDTH
win_h           dd DEFAULT_HEIGHT

; Window label
label           db "AСlock", 0

; Token delimiter list for command line
delimiters	db 9, 10, 11, 12, 13, 32, 0 ; FIXME: Chars? 

;---------------- Uninitialized data ----------------;

align 16
_image_end:

win_colors      KOS_SYS_COLORS_S

; Space for command line. at the end we have an additional
; byte for a terminating zero
cmd_line        rb 257

; Reserve for stack:
                rb 512
align 16
_stacktop:
_memory:
