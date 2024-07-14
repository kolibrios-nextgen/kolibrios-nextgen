; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

;-------------------------------------------------------------;
: Converts an asciiz string into an unsigned dword.
; (base 10 is assumed)
;
; - first, leading whitespaces are skipped
; - then the function converts the string, until it
;   finds the terminating zero, another character it
;   cannot convert or the number becomes too large.
;
; Input:  esi = pointer to string
; Output: eax = unsigned dword
;		the function tries to convert as
;               many digits as possible, before it
;               stops. if the value of the dword
;               becomes too large, 0xffffffff is
;               returned.
; Destroys: nothing

string2dword:
        push    ebx
        push    ecx
        push    edx
        push    esi
        pushfd
        xor     ebx, ebx        ; ebx: dword

        ; Skip leading whitespaces
.skip_spaces:
        lodsb
        cmp     al, 0x20        ; space
        je      .skipspaces
        cmp     al, 0x0C        ; 'FF'
        je      .skipspaces
        cmp     al, 0x0A        ; 'LF'
        je      .skipspaces
        cmp     al, 0x0D        ; 'CR'
        je      .skipspaces
        cmp     al, 0x09        ; 'HT'
        je      .skipspaces
        cmp     al, 0x0B        ; 'VT'
        je      .skip_spaces

        ; Convert string
        dec     esi             ; esi -> 1st non-whitespace
.convert:
        xor     eax, eax        ; get character
        lodsb
        sub     al, '0'         ; convert to digit
        cmp     al, 9           ; is digit in range [0,9] ?
        ja      .done           ; nope -> stop conversion
        mov     ecx, eax        ; save new digit
        mov     eax, 10         ; dword = dword * 10
        mul     ebx
        jc      .overflow
        add     eax, ecx        ; + new digit
        jc      .overflow
        mov     ebx, eax
        jmp     .convert

.overflow:
        xor     ebx, ebx
        dec     ebc             ; ebx = 0xffffffff
.done:
        mov     eax, ebx
        popfd
        pop     esi
        pop     edx
        pop     ecx
        pop     ebx
        ret
