; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

; strlen()
; Returns the length of an asciiz string
; Input:    esi = pointer to string
; Output:   eax = string length
; Destroys: nothing

strlen:
        push    ecx
        push    edi
        pushfd
        cld
        mov     ecx, -1
        mov     edi, esi        ; find terminating zero
        xor     al, al
        repne   scasb
        mov     eax, edi        ; calculate string length
        sub     eax, esi
        dec     eax
        popfd
        pop     edi
        pop     ecx
        ret
