; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG Team

; Author of the original version on NASM:
; Thomas Mathys <killer@vantage.ch>

; ------------------ Constants ----------------------;

DATE_WIDTH = 48

;---------------------- Code ------------------------;

; draw_clock()
; Draw the clock
; Input:    nothing
; Output:   nothing
; Destroys: nothing

draw_clock:
virtual at ebp-.LOCAL_SIZE
.locals:
.i              dd ?
.tm_r1_x        dd ?
.tm_r1_y        dd ?
.tm_r2_x        dd ?
.tm_r2_y        dd ?
.sec_r_x        dd ?
.sec_r_y        dd ?
.min_r_x        dd ?
.min_r_y        dd ?
.hour_r_x       dd ?
.hour_r_y        dd ? 
.work_width     dd ?
.work_height    dd ?
.tmp            dd ?
.LOCAL_SIZE = $ - .locals
end virtual

        enter	.LOCAL_SIZE, 0
        pushad
        pushfd

        ; Get window dimensions
        mcall   SF_THREAD_INFO, thread_info, -1

        ; Calculate work area size (width/height = ecx/edx)
        ; If the work area is too small (maybe the window is shaded)
        ; we don't draw anything.
        mcall   SF_STYLE_SETTINGS, SSF_GET_SKIN_HEIGHT
        mov     ecx, [thread_info + KOS_THREAD_INFO_S.win_w]
        sub     ecx, KOS_WIN_SKIN_BORDER_LEFT + KOS_WIN_SKIN_BORDER_RIGHT
        mov     edx, [thread_info + KOS_THREAD_INFO_S.win_h]
        sub     edx, eax
        sub     edx, KOS_WIN_SKIN_BORDER_BOTTOM
        cmp     ecx, 0                  ; width too small ?
        jle     .bye
        cmp     edx, 0                  ; height too small ?
        jnle    .continue
.bye:
        jmp     .byebye
.continue:
        mov     [.work_width], ecx       ; save for later (for fpu)
        mov     [.work_height], edx

        ; Calculate center of clock (x/y = esi/edi)
        mov     esi, [thread_info + KOS_THREAD_INFO_S.win_w]
        shr     esi, 1
        mov     edi, [thread_info + KOS_THREAD_INFO_S.win_h]
        sub     edi, KOS_WIN_SKIN_BORDER_BOTTOM
        sub     edi, eax
        shr     edi, 1
        add     edi, eax

        ; Clear work area
        pushad
        mov     ebx, KOS_WIN_SKIN_BORDER_LEFT*0x10000   ; x start
        or      ebx, ecx                                ; width
        inc     ebx
        mov     ecx, eax        ; y start
        shl     ecx, 16         ; (= skin height)
        or      ecx, edx        ; height
        inc     ecx
        mov     edx, [win_colors+KOS_SYS_COLORS_S.work]
        mov     eax, SSF_REDRAW_RECT
        mcall
        popad

        ; Calculate second hand radii
        fild    dword [.work_width]
        fmul    dword [sec_r_factor]
        fstp    dword [.sec_r_x]
        fild    dword [.work_height]
        fmul    dword [sec_r_factor]
        fstp    dword [.sec_r_y]

        ; Calculate minute hand radii
        fild    dword [.work_width]
        fmul    dword [min_r_factor]
        fstp    dword [.min_r_x]
        fild    dword [.work_height]
        fmul    dword [min_r_factor]
        fstp    dword [.min_r_y]

        ; Calculate hour hand radii
        fild    dword [.work_width]
        fmul    dword [hour_r_factor]
        fstp    dword [.hour_r_x]
        fild    dword [.work_height]
        fmul    dword [hour_r_factor]
        fstp    dword [.hour_r_y ]

        ; Calculate tick mark radii
        fild    dword [.work_width]
        fmul    dword [tm_r1_factor]
        fstp    dword [.tm_r1_x]
        fild    dword [.work_height]
        fmul    dword [tm_r1_factor]
        fstp    dword [.tm_r1_y]
        fild    dword [.work_width]
        fmul    dword [tm_r2_factor]
        fstp    dword [.tm_r2_x]
        fild    dword [.work_height]
        fmul    dword [tm_r2_factor]
        fstp    dword [.tm_r2_y]

        ; Get system time (edx)
        mcall   SF_GET_SYS_TIME
        mov     edx, eax

        ; Draw second hand
        push    edx
        mov     eax, edx
        shr     eax, 16
        call    bcdbin
        mov     ecx, eax        ; save seconds for later
        push    ecx
        push    eax
        push    0.104719755     ; 2*pi/60
        push    dword [.sec_r_x]
        push    dword [.sec_r_y]
        push    esi
        push    edi
        call    get_hand_coords
        mov     eax, SF_DRAW_LINE
        shl     ebx, 16
        or      ebx, esi
        shl     ecx, 16
        or      ecx, edi
        mov     edx, [win_colors+KOS_SYS_COLORS_S.work_text]
        mcall
        pop     ecx
        pop     edx

        ; Draw minute hand
        push    edx
        mov     eax, edx
        shr     eax, 8
        call    bcdbin
        mov     edx, 60
        mul     edx
        add     eax, ecx
        mov     ecx, eax        ; save for later
        push    ecx
        push    eax
        push    0.001745329     ; 2*pi/60/60
        push    dword [.min_r_x]
        push    dword [.min_r_y]
        push    esi
        push    edi
        call    get_hand_coords
        mov     eax, SF_DRAW_LINE
        shl     ebx, 16
        or      ebx, esi
        shl     ecx, 16
        or      ecx, edi
        mov     edx, [win_colors+KOS_SYS_COLORS_S.work_text]
        mcall
        pop     ecx
        pop     edx

        ; Draw hour hand
        push    edx
        mov     eax, edx
        call    bcdbin
        cmp     eax, 11         ; % 12 (just to be sure)
        jnae    .hours_ok
        sub     eax, 12
.hours_ok:
        mov     edx, 60*60
        mul     edx
        add     eax,ecx
        push    eax
        push    0.000145444     ; 2*pi/60/60/12
        push    dword [.hour_r_x]
        push    dword [.hour_r_y ]
        push    esi
        push    edi
        call    get_hand_coords
        mov     eax, SF_DRAW_LINE
        shl     ebx, 16
        or      ebx, esi
        shl     ecx, 16
        or      ecx, edi
        mov     edx, [win_colors+KOS_SYS_COLORS_S.work_text]
        mcall
        pop     edx
    
        ; Draw tick marks
        mov    dword [.i], 11    ; draw 12 marks
.draw_tick_marks:
        push    dword [.i]       ; calculate start point
        push    0.523598776     ; 2*pi/12
        push    dword [.tm_r1_x]
        push    dword [.tm_r1_y]
        push    esi
        push    edi
        call    get_hand_coords
        mov     eax, ebx        ; save in eax and edx
        mov     edx, ecx
        push    dword [.i]
        push    0.523598776     ; 2*pi/12
        push    dword [.tm_r2_x]
        push    dword [.tm_r2_y]
        push    esi
        push    edi
        call    get_hand_coords
        shl     eax, 16
        shl     edx, 16
        or      ebx, eax        ; ebx = x start and end
        or      ecx, edx        ; ecx = y start and end
        mcall   SF_DRAW_LINE,, [win_colors+KOS_SYS_COLORS_S.work_text]
        dec     dword [.i]
        jns     .draw_tick_marks

        ; Calculate text start position
        mov     eax, [thread_info+KOS_THREAD_INFO_S.win_w]
        sub     eax, DATE_WIDTH         ; x = (wndwidth-textwidth)/2
        shr     eax, 1                  ; eax = x
        fild    dword [.work_height]     ; y = date_factor*.work_height...
        fmul    dword [date_factor]
        mov     [.tmp], edi              ; ... + y_clock_center
        fiadd   dword [.tmp]
        fistp   dword [.tmp]
        mov     ebx, [.tmp]              ; ebx = y

        ; Draw text at all ?
        cmp     dword [.work_width], DATE_WIDTH   ; text too wide ?
        jb      .goodbye
        mov     ecx, ebx                          ; text too high ?
        add     ecx, 10-1
        mov     edx, [thread_info+KOS_THREAD_INFO_S.win_h]
        sub     edx, KOS_WIN_SKIN_BORDER_BOTTOM
        cmp     ecx, edx
        jnae    .draw_all
.goodbye:
        jmp     .bye
.draw_all:
        ; ebx = (x << 16) | y
        shl     eax, 16
        or      ebx, eax

        ; Get date (edi)
        mcall   SF_GET_SYS_DATE
        mov     edi, eax

        ; Display month
        mov     eax, edi        ; get month
        shr     eax, 8
        call    bcdbin

        ; ebx contains already position    
        mov     ecx, [win_colors+KOS_SYS_COLORS_S.work_text]
        lea     edx, [month_names-3+eax*2+eax]   ; -3 because eax = 1..12
        mov     esi, 3                           ; text length
        mov     eax, SF_DRAW_TEXT
        mcall

        ; Display date
        add     ebx, ((3*6+3) and 0xFFFF) shl 16
        mov     eax, edi                ; get date
        shr     eax, 16
        call    bcdbin
        mov     edx, ebx                ; position must be in edx
        mov     ebx, 0x00020000         ; number, display two digits
        mov     ecx, eax                ; number to display
        mov     esi, [win_colors+KOS_SYS_COLORS_S.work_text]
        mov     eax, SF_DRAW_NUMBER
        mcall

        ; Display year. the way we avoid the y2k bug is even
        ; simpler, yet much better than in the last version:
        ; now we simply display the last two digits and let the
        ; user decide wether it's the year 1903 or 2003.
        add     edx, ((2*6+3) and 0xFFFF) shl 16
        mov     eax, edi        ; get year
        call    bcdbin
        mov     ebx, 0x00020000 ; number, display two digits
        mov     ecx, eax        ; number to display
                                ; edx contains already position
        mov     esi, [win_colors+KOS_SYS_COLORS_S.work_text]
        mov     eax, SF_DRAW_NUMBER
        mcall

.byebye:
        popfd
        popad
        ret

; bcdbin()
; Converts a 8 bit bcd number into a 32 bit binary number
;
; Input:        al = 8 bit bcd number
; Output:       eax = 32 bit binary number
; Destroys:     dl, flags

bcdbin:
        push    edx
        pushfd
        mov    dl, al   ; save bcd number
        shr    al, 4    ; convert upper nibble
        mov    ah, 10
        mul    ah
        and    dl, 15   ; add lower nibble
        add    al, dl
        and    eax, 255
        popfd
        pop    edx
        ret

; get_hand_coords()
; Calculates the end point of a hand
; Input (on stack, push from top to bottom):
;   .angle        angle (integer)
;   .deg2rad      conversion factor for ANGLE (32 bit real)
;   .radius_x     x radius (32 bit real)
;   .radius_y     y radius (32 bit real)
;   .center.x     x center of the clock (integer)
;   .center_y     y center of the clock (integer)
; Output:
; ebx = x coordinate in bits 0..15, bits 16..31 are zero
; ecx = y coordinate in bits 0..15, bits 16..31 are zero
; Destroys: nothing

get_hand_coords:
virtual at ebp+8
.center_y        dd ?
.center_x        dd ?
.radius_y       dd ?
.radius_x       dd ?
.deg2rad        dd ?
.angle          dd ?
end virtual

        enter   0,0
        pushfd

        fild    dword [.angle]  ; get angle
        fmul    dword [.deg2rad]    ; convert to radians
        fsincos
        fmul    dword [.radius_y]    ; -y * radius + clockcy
        fchs
        fiadd   dword [.center_x]
        fistp   dword [.center_y]    
        fmul    dword [.radius_x]    ; x * radius + clockcx
        fiadd   dword [.center_y]
        fistp   dword [.center_x]
    
        mov ebx, [.center_x]
        mov ecx, [.center_y]

        popfd
        leave
        ret     4*6

;----------------- Initialized data -----------------;

tm_r1_factor     dd      0.45
tm_r2_factor     dd      0.426315789
sec_r_factor     dd      0.378947368
min_r_factor     dd      0.355263158
hour_r_factor    dd      0.189473684
date_factor     dd      0.1

month_names:
        db "Jan"
        db "Feb"
        db "Mar"
        db "Apr"
        db "May"
        db "Jun"
        db "Jul"
        db "Aug"
        db "Sep"
        db "Oct"
        db "Nov"
        db "Dec"
