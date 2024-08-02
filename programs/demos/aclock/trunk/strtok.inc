; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

; strtok()
; This function works like strtok from a c runtime library.
; Note that it is not threadsafe. it would be an easy task.
; To make it threadsafe, though:
; .adx must be removed, instead the last search address is
; stored at some location provided by the user (passed as
; a third parameter in ecx or so)
; Input:
;       eax: address of string to be searched (asciiz), or
;            0 to get the next token of the current string
;       ebx: address of delimiter list (asciiz)
; Output:
;       eax: pointer to the next token, or 0 if there
;            aren't any tokens anymore.
; Destroys: 
;       nothing
strtok:
        pushad
        pushfd

        ; Get start address
        ; If the new start address is 0, and the old address (.adx)
        ; is also 0, then there's nothing to do and we return 0.
        or      eax, eax                ; new address =  0 ?
        jz      .no_new_string          ; nope -> use old string
        mov     [.adx], eax             ; yeah -> store new string adx
.no_new_string:
        mov     esi, [.adx]             ; load string address
        or      esi, esi                ; 0 ?
        jnz     .start_adx_ok           ; nope -> ok
        xor     eax, eax                ; yeah -> return 0
        je      .bye
.start_adx_ok:
        ; Skip leading delimiters
.skip_delimiters:
        lodsb                           ; read character
        mov     edi, ebx                ; edi -> delimiter list
.try_next_delim:
        mov     cl, [edi]               ; get delimiter
        inc     edi
        or      cl, cl                  ; end of delimiter list
        jz      .end_of_delimiter_list
        cmp     al, cl                  ; if AL is a delimiter, then
        je      .skip_delimiters        ; we need to skip it too...
        jmp     .try_next_delim         ; otherwise try next delimiter
.end_of_delimiter_list:
        ; End of string reached without finding any non-delimiters ?
        or      al, al                  ; character = 0 ?
        jnz    .continue                ; nope -> continue
        xor     eax, eax
        mov     dword [.adx], eax       ; yeah -> remember this
        jmp     .bye
.continue:
        ; Found the start of a token, let's store its address
        mov     edx, esi
        dec     edx                     ; edx = start address of token

        ; Find the end of the token
.find_end_of_token:
        lodsb                           ; get character
        mov     edi, ebx                ; edi -> delimiter list
.try_next_delim2:
        mov     cl, [edi]               ; get delimiter
        inc     edi
        cmp     al, cl                  ; is AL a delimiter ?
        jne     .continue2              ; nope -> continue
        or      al, al                  ; terminating zero found ?
        jnz     .mark_end_of_token
        xor     esi, esi                ; yeah -> remember this
        jmp     .remeber_search_addr
.mark_end_of_token:
        mov    byte [esi-1], 0          ; nope -> mark end of token
.remeber_search_addr:
        mov    [.adx], esi              ; remember search address
        mov    eax, edx                 ; return token address
        jmp    .bye
.continue2:
        or      cl, cl                  ; end of delimiter list ?
        jnz     .try_next_delim2        ; nope -> try next delimiter
        jmp     .find_end_of_token
        
        ; Write return value into stack, so that when popad
        ; gets executed, eax will receive the return value.
.bye:
        mov     [esp+4*8], eax
        popfd
        popad
        ret

.adx    dd      0
