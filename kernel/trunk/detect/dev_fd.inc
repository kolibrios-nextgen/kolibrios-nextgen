;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                              ;;
;; Copyright (C) KolibriOS team 2004-2015. All rights reserved. ;;
;; Distributed under terms of the GNU General Public License    ;;
;;                                                              ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

$Revision$


;***************************************************
;      clear the DRIVE_DATA table,
;      search for FDDs and add them into the table
;      author - Mario79
;***************************************************
        xor     eax, eax
        mov     edi, DRIVE_DATA
        mov     ecx, DRIVE_DATA_SIZE/4
        cld
        rep stosd

