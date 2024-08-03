; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2006-2021 KolibriOS Team
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; A simple application example for KolibriOS-NG.
; Compile with FASM:
;   You can open example.asm through the FASM program (its shortcut is
;   on the desktop). Or you can just press F9 in Tinypad or CEdit.
;   Compilation log displayed on the debug board (BOARD program).

format binary as ""     ; Binary file format without extension
use32                   ; Use 32 bit instructions
org 0                   ; the base address of application, always 0x0

;---------------------------- Application header -----------------------------;

db      'MENUET01'      ; Signature
dd      1               ; Header version
dd      START           ; Entry point
dd      I_END           ; End of image
dd      MEM             ; End of memory
dd      STACKTOP        ; Address of stack top
dd      0               ; Buffer for command line arguments (0 if not used)
dd      0               ; Buffer for path (0 if not used)

;--------------------------------- Includes ----------------------------------;

include 'kosapi.inc'                    ; This file provides basic constants
                                        ; and macros for the KolibriOS-NG API

;--------------------------------- Constants ---------------------------------;

LINE_LEN = 40                           ; Line length

;----------------------------------- Code ------------------------------------;

START:                                  ; Start of execution
        call    draw_window             ; Draw the window

; After the window is drawn, it's practical to have the main loop.

event_wait:
        mov     eax, SF_WAIT_EVENT      ; Function SF_WAIT_EVENT(10):
                                        ; waiting event (event type is
                                        ; returned in eax).
        mcall                           ; Without arguments, "mcall" macro is
                                        ; simply replaced with "int 0x40"

        cmp     eax, KOS_EV_REDRAW      ; Event redraw request ?
        je      redraw                  ; Expl.: there has been activity on
                                        ; screen and parts of the applications
                                        ; has to be redrawn.

        cmp     eax, KOS_EV_KEY         ; Event key in buffer ?
        je      key                     ; Expl.: User has pressed a key while
                                        ; the app is at the top of the window
                                        ; stack.

        cmp     eax, KOS_EV_BUTTON      ; Event button in buffer ?
        je      button                  ; Expl.: User has pressed one of the
                                        ; applications buttons.
 
        jmp     event_wait              ; Wait for the event again.

redraw:                                 ; Redraw event handler.
        call    draw_window             ; We call the window_draw function and
        jmp     event_wait              ; jump back to event_wait.

key:                                    ; Keypress event handler
        mov     eax, SF_GET_KEY         ; The key is returned in ah.
        mcall                           ; The keymust be read and cleared from
                                        ; the system queue.

        jmp     event_wait              ; Just read the key, ignore it and jump
                                        ; to event_wait.

button:                                 ; Button press event handler.
        mov     eax, SF_GET_BUTTON      ; Function SF_GET_BUTTON(8):
                                        ; get pressed button number.
        mcall                           ; Button number returned to ah.

        cmp     ah, 1                   ; Button id == 1 ? 
                                        ; id = 1 is always the "exit" button.
        jne     noclose

        ; The 'mcall' macro can also be used with arguments.
        ; That is, the first argument will be placed in eax,
        ; the second in ebx, etc.
        mcall   SF_TERMINATE_PROCESS    ; Function SF_TERMINATE_PROCESS(-1):
                                        ; terminate this program.

noclose:
        jmp     event_wait              ; Wait for the event again.


; Window definition and draw.

draw_window:
        ; Start window draw.
        mcall   SF_REDRAW, SSF_BEGIN_DRAW
 
        mov     eax, SF_CREATE_WINDOW   ; Function SF_CREATE_WINDOW(0): 
                                        ; define and draw window.
        mov     ebx, 100 * 65536 + 300  ; [x start] *65536 + [x size]
        mov     ecx, 100 * 65536 + 120  ; [y start] *65536 + [y size]
        mov     edx, 0x14ffffff         ; Color of work area RRGGBB
                                        ; 0x02000000 = window type 4
                                        ; (fixed size, skinned window).
        mov     esi, 0x808899ff         ; Color of grab bar RRGGBB,
                                        ; 0x80000000 = color glide.
        mov     edi, title              ; Set window title.
        mcall
 
        mov     eax, SF_DRAW_TEXT       ; Function SF_DRAW_TEXT(4):
                                        ; draw text string.
        mov     ebx, 25 * 65536 + 35    ; Text coordinates.
        mov     ecx, 0x00224466         ; Text style 0xXXRRGGBB.
        mov     edx, text               ; Address to text lines.
        mov     esi, LINE_LEN           ; Line length.
 
  .newline:                             ; Draw new line.
        mcall
        add     ebx, 10
        add     edx, LINE_LEN
        cmp     byte[edx], 0            ; Search for null terminator
        jne     .newline
 
        ; End window draw.
        mcall   SF_REDRAW, SSF_END_DRAW
 
        ret
 
;------------------------------ Initialized data -----------------------------;

; Data can be freely mixed with code in any part of the image.
; Only the header information is required at the beginning of the image.
 
text    db  "It looks like you have just compiled    "
        db  "your first program for KolibriOS-NG.    "
        db  "                                        "
        db  "Congratulations!                        ", 0

title   db  "Example application", 0

;----------------------------- Uninitialized data ----------------------------;

I_END:
        rb 4096                         ; Reserved 4Kb for stack
align 16
STACKTOP:

MEM:
