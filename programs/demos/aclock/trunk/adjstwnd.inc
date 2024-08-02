; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

; adjust_window_dimensions()
; Adjust window dimensions to get a certain work area size
;  - first the window width and height are adjusted
;    and clamped if they're too large for the screen.
;  - then the window positions are adjusted, if the
;    window goes out of the screen.
; Input:
;	ebx - window x position;
;	ecx - window y position;
;	edx - desired work area width;
;	esi - desired work area height.
; Output:
;	eax - return code (0 = ok, -1 = invalid window type);
;	ebx - adjusted window x position;
;	ecx - adjusted window y position;
;	edx - window width to get desired work area width;
;	esi - window height to get desired work area height.
; Destroys:
;	nothing.

; Normally x and y are the upper left corner of the window,
; relative to the upper left corner of the screen.
; if you pass a negative x or y it will be treated as the
; lower right corner of the window, relative to the lower
; right corner of the screen.

adjust_window_dimensions:
        push    edi
        push    ebp
        pushfd

        ; Adjust width (edx)
        add	edx, KOS_WIN_SKIN_BORDER_LEFT+KOS_WIN_SKIN_BORDER_RIGHT

        ; Adjust height (esi). we need the skin height to do this.
        push	ebx
        mcall   SF_STYLE_SETTINGS, SSF_GET_SKIN_HEIGHT
        pop     ebx
	lea	esi, [esi+eax+KOS_WIN_SKIN_BORDER_BOTTOM]

        ; Сlamp window dimensions
        mcall   SF_GET_SCREEN_SIZE      ; get screen dimensions
        mov     edi, eax                ; edi = screen width
        shr     edi, 16
        movzx   ebp, ax                 ; ebp = screen height
        cmp     edx, edi                ; window width > screen width ?
        jna     .width_ok
        mov     edx, edi                ; yes -> use screen width
.width_ok:
        cmp     esi, ebp                ; wnd height > screen height ?
        jna     .height_ok
        mov     esi, ebp                ; yes -> use screen height
.height_ok:
        ; Adjust x position
        or      ebx, ebx                 ; do the lower right corner
        jns     .x_neg                  ; stuff if x is negative.
        add     ebx, edi
        sub     ebx, edx
.x_neg:
        or      ebx, ebx                ; x < 0 ?
        jns     .x_not_neg
        xor     ebx, ebx                ; yes -> x = 0
.x_not_neg:
        mov     eax, ebx                ; x + width > screen width ?
        add     eax, edx
        cmp     eax, edi
        jna     .x_ok
        sub     eax, edi                ; yes -> adjust
        sub     ebx, eax
.x_ok:
        ; Adjust y position
        or      ecx, ecx                ; do the lower right corner
        jns     .y_neg                  ; stuff if y is negative.
        add     ecx, ebp
        sub     ecx, esi
.y_neg:
        or      ecx, ecx                ; y < 0 ?
        jns     .y_not_neg
        xor	ecx,ecx                 ; yes -> y = 0
.y_not_neg:
        mov     eax, ecx                ; y + height > screen height ?
        add     eax, esi
        cmp     eax, ebp
        jna     .done
        sub     eax, ebp                ; yes -> adjust
        sub     ecx, eax

.done:
        popfd
        pop     ebp
        pop     edi
        ret
