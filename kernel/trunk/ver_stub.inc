; These are stub macros for building the kernel 
; without git or without the version-gen.sh script. 
; You can change this file to ver.inc so that the kernel 
; is built correctly.

macro VERSION_INFO {
        db  0, 0
        dw  0
.hash   db  '?????????', 0
}

macro BOOT_VERSION_INFO {
        db  'v0.0-0        ',13,10,13,10,0
}
