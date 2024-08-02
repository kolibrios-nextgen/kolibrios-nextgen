; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>


; parse_command_line()
; Command line parsing code for Aclock
; Input:    nothing
; Output:   win_x_pos, win_y_pos, win_w, win_h 
; Destroys: nothing

parse_command_line:
        pushad
        pushfd

        ; Terminate command line, just to be sure
        xor     ah, ah
        mov     byte [cmd_line + 256], ah

        ; Go through all tokens
        mov     eax, cmd_line           ; eax -> command line
.parse_loop:
        mov     ebx, delimiters         ; ebx -> token delimiter list
        call    strtok                  ; get next parameter
        or      eax, eax                ; no more parameters ?
        jz     .no_more_tokens
        mov     cl, [eax]               ; get 1st char of parameter
        cmp     cl, 'x'                 ; which parameter is it ?
        je     .param_x
        cmp     cl, 'y'
        je     .param_y
        cmp     cl, 'w'
        je     .param_w
        cmp     cl, 'h'
        je     .param_h

        ; If we reach this line it's an unknown parameter, ignore it
.next_param:
        xor     eax, eax                ; set eax = 0 to continue
        jmp     .parse_loop             ; after last token.
.no_more_tokens:
        popfd
        popad
        ret

        ; eax -> first character of the parameter
.param_x:
        push    eax
        call    parse_position_param
        mov     [win_x_pos], eax
        pop     eax
        jmp     .next_param

        ; eax -> first character of the parameter
.param_y:
        push    eax
        call    parse_position_param
        mov     [win_y_pos], eax
        pop     eax
        jmp     .next_param

        ; eax -> first character of the parameter
.param_w:
        push    eax
        call    parse_size_param
        mov     [win_w], eax
        pop     eax
        jmp     .next_param

        ; eax -> first character of the parameter
.param_h:
        push    eax
        call    parse_size_param
        mov     [win_h], eax
        pop     eax
        jmp     .next_param


; parse_position_param()
; Parse position parameter
; Input:    eax = address of first character of parameter
; Output:   eax contains position
; Destroys: nothing

parse_position_param:
        push     ebx
        push     esi
        pushfd

        ; Is the second char of the parameter a '-' ?
        inc     eax
        xor     ebx, ebx        
        cmp     byte [eax], '-'
        jne     .no_minus
        mov     ebx, 1                  ; yes -> set flag
        inc     eax                     ; ...and move to next char
.no_minus:
        ; Convert rest of parameter to dword
        mov     esi, eax
        call    string2dword

        ; Negate if necessary
        or     ebx, ebx
        jz     .done
        neg     eax
.done:
        popfd
        pop     esi
        pop     ebx
        ret


; parse_size_param()
; Parse dimension parameter
; Input:    eax = address of first char of parameter
; Output:   eax = contains dimension
; Destroys: nothing

parse_size_param:
        push    esi
        pushfd
        lea     esi, [eax + 1]          ; esi -> 2nd char of parameter
        call    string2dword
        popfd
        pop     esi
        ret
