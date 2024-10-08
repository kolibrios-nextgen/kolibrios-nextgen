; SPDX-License-Identifier: GPL-2.0-only
; SPDX-FileCopyrightText: 2024 KolibriOS-NG team

; This file contains the constants required for the KolibriOS-NG API.

; System calls:
; SF_ and SSF_ and SSSF_ constant prefixes are reserved for system functions,
; subfunctions, and subsubfunctions.

; Сonstants:
; The constant name must be in uppercase and must also contain the KOS_ prefix.
; Exception: POSIX constants.

; Structures:
; The structure name must be in uppercase and contain the KOS_ prefix
; as well as the _S postfix. For example: KOS_THREAD_INFO_S.

;----------------- System functions -----------------;

SF_TERMINATE_PROCESS = -1
SF_CREATE_WINDOW = 0
SF_PUT_PIXEL = 1
SF_GET_KEY = 2
SF_GET_SYS_TIME = 3
SF_DRAW_TEXT = 4
SF_SLEEP = 5
SF_PUT_IMAGE = 7
SF_DEFINE_BUTTON = 8
SF_THREAD_INFO = 9
SF_WAIT_EVENT = 10
SF_CHECK_EVENT = 11
SF_REDRAW = 12
  SSF_BEGIN_DRAW = 1
  SSF_END_DRAW = 2
SF_DRAW_RECT = 13
SF_GET_SCREEN_SIZE = 14
SF_BACKGROUND_SET = 15
  SSF_SIZE_BG = 1
  SSF_PIXEL_BG = 2
  SSF_REDRAW_BG = 3
  SSF_MODE_BG = 4
  SSF_IMAGE_BG = 5
  SSF_MAP_BG = 6
  SSF_UNMAP_BG = 7
  SSF_LAST_DRAW = 8
  SSF_REDRAW_RECT = 9
SF_RD_TO_FLOPPY = 16
SF_GET_BUTTON = 17
SF_SYSTEM = 18
  SSF_UNFOCUS_WINDOW = 1
  SSF_TERMINATE_THREAD = 2
  SSF_FOCUS_WINDOW = 3
  SSF_GET_IDLE_COUNT = 4
  SSF_GET_CPU_FREQUENCY = 5
  SSF_RD_TO_HDD = 6
  SSF_GET_ACTIVE_WINDOW = 7
  SSF_SPEAKER = 8
    SSSF_GET_STATE = 1
    SSSF_TOGGLE = 2
  SSF_SHUTDOWN = 9
  SSF_MINIMIZE_WINDOW = 10
  SSF_INFO_DISC_SYS = 11
  SSF_KERNEL_VERSION = 13
  SSF_WAIT_RETRACE = 14
  SSF_CURSOR_CENTER = 15
  SSF_GET_FREE_RAM = 16
  SSF_GET_TOTAL_RAM = 17
  SSF_TERMINATE_THREAD_ID = 18
  SSF_MOUSE_SETTINGS = 19
    SSSF_GET_SPEED = 0
    SSSF_SET_SPEED = 1
    SSSF_GET_SPEEDUP = 2
    SSSF_SET_SPEEDUP = 3
    SSSF_SET_POS = 4
    SSSF_SET_BUTTON = 5
    SSSF_GET_DOUBLE_CLICK_DELAY = 6
    SSSF_SET_DOUBLE_CLICK_DELAY = 7
  SSF_GET_RAM_INFO = 20
  SSF_GET_THREAD_SLOT = 21
  SSF_FOREIGN_WINDOW = 22
    SSSF_MINIMIZE = 0
    SSSF_MINIMIZE_ID = 1
    SSSF_RESTORE = 2
    SSSF_RESTORE_ID = 3
  SSF_MINIMIZE_ALL = 23
  SSF_SET_SCREEN_LIMITS = 24
  SSF_WINDOW_BEHAVIOR = 25
    SSSF_GET_WB = 1
    SSSF_SET_WB = 2
SF_MIDI = 20
  SSF_RESET = 1
  SSF_OUTPUT = 2
SF_SYSTEM_SET = 21
  SSF_MPU_MIDI_BASE = 1
  SSF_KEYBOARD_LAYOUT = 2
  SSF_SYS_LANG = 5
  SSF_ACCESS_HD_LBA = 11
  SSF_ACCESS_PCI = 12
SF_SET_TIME_DATE = 22
SF_WAIT_EVENT_TIMEOUT = 23
SF_CD = 24
  SSF_EJECT_TRAY = 4
  SSF_INSERT_TRAY = 5
SF_SCREEN_PUT_IMAGE = 25
SF_SYSTEM_GET = 26
  SSF_TIME_COUNT = 9
  SSF_TIME_COUNT_PRO = 10
SF_GET_SYS_DATE = 29
SF_CURRENT_FOLDER = 30
  SSF_SET_CF = 1
  SSF_GET_CF = 2
  SSF_ADD_SYS_FOLDER = 3
SF_GET_PIXEL_OWNER = 34
SF_GET_PIXEL = 35
SF_GET_IMAGE = 36
SF_MOUSE_GET = 37
  SSF_SCREEN_POSITION = 0
  SSF_WINDOW_POSITION = 1
  SSF_BUTTON = 2
  SSF_BUTTON_EXT = 3
  SSF_LOAD_CURSOR = 4
  SSF_SET_CURSOR = 5
  SSF_DEL_CURSOR = 6
  SSF_SCROLL_DATA = 7
SF_DRAW_LINE = 38
SF_BACKGROUND_GET = 39
; Сoincide with SF_BACKGROUND_SET
  ;SSF_SIZE_BG = 1
  ;SSF_PIXEL_BG = 2
  ;SSF_MODE_BG = 4
SF_SET_EVENTS_MASK = 40
SF_PORT_IN_OUT = 43
SF_SET_PORTS = 46
SF_DRAW_NUMBER = 47
SF_STYLE_SETTINGS = 48
  SSF_APPLY = 0
  SSF_SET_BUTTON_STYLE = 1
  SSF_SET_COLORS = 2
  SSF_GET_COLORS = 3
  SSF_GET_SKIN_HEIGHT = 4
  SSF_GET_SCREEN_AREA = 5
  SSF_SET_SCREEN_AREA = 6
  SSF_GET_SKIN_MARGINS = 7
  SSF_SET_SKIN = 8
  SSF_GET_FONT_SMOOTH = 9
  SSF_SET_FONT_SMOOTH = 10
  SSF_GET_FONT_SIZE = 11
  SSF_SET_FONT_SIZE = 12
SF_APM = 49
SF_SET_WINDOW_SHAPE = 50
SF_CREATE_THREAD = 51
SF_CLIPBOARD = 54
  SSF_GET_SLOT_COUNT = 0
  SSF_READ_CB = 1
  SSF_WRITE_CB = 2
  SSF_DEL_SLOT = 3
  SSF_UNLOCK_BUFFER = 4
SF_SPEAKER_PLAY = 55
SF_PCI_BIOS = 57
SF_IPC = 60
  SSF_SET_AREA = 1
  SSF_SEND_MESSAGE = 2
SF_GET_GRAPHICAL_PARAMS = 61
  SSF_SCREEN_SIZE = 1
  SSF_BITS_PER_PIXEL = 2
  SSF_BYTES_PER_LINE = 3
SF_PCI = 62
  SSF_GET_VERSION = 0
  SSF_GET_LAST_BUS = 1
  SSF_GET_ADRR_MODE = 2
  SSF_READ_BYTE = 4
  SSF_READ_WORD = 5
  SSF_READ_DWORD = 6
  SSF_WRITE_BYTE = 8
  SSF_WRITE_WORD = 9
  SSF_WRITE_DWORD = 10
SF_BOARD = 63
  SSF_DEBUG_WRITE = 1
  SSF_DEBUG_READ = 2
SF_MEMORY_RESIZE = 64
SF_PUT_IMAGE_EXT = 65
SF_KEYBOARD = 66
  SSF_SET_INPUT_MODE = 1
  SSF_GET_INPUT_MODE = 2
  SSF_GET_CONTROL_KEYS = 3
  SSF_SET_SYS_HOTKEY = 4
  SSF_DEL_SYS_HOTKEY = 5
  SSF_LOCK_INPUT = 6
  SSF_UNLOCK_INPUT = 7
SF_CHANGE_WINDOW = 67
SF_SYS_MISC = 68
  SSF_GET_TASK_SWITCH_COUNT = 0
  SSF_SWITCH_TASK = 1
  SSF_PERFORMANCE = 2
    SSSF_ALLOW_RDPMC = 0
    SSSF_CACHE_STATUS = 1
    SSSF_CACHE_ON = 2
    SSSF_CACHE_OFF = 3
  SSF_READ_MSR = 3
  SSF_WRITE_MSR = 4
  SSF_HEAP_INIT = 11
  SSF_MEM_ALLOC = 12
  SSF_MEM_FREE = 13
  SSF_WAIT_SIGNAL = 14
  SSF_LOAD_DRIVER = 16
  SSF_CONTROL_DRIVER = 17
  SSF_LOAD_DLL = 19
  SSF_MEM_REALLOC = 20
  SSF_LOAD_DRIVER_PE = 21
  SSF_MEM_OPEN = 22
  SSF_MEM_CLOSE = 23
  SSF_SET_EXCEPTION_HANDLER = 24
  SSF_SET_EXCEPTION_STATE = 25
  SSF_MEM_FREE_EXT = 26
  SSF_LOAD_FILE = 27
SF_DEBUG = 69
  SSF_SET_MESSAGE_AREA = 0
  SSF_GET_REGISTERS = 1
  SSF_SET_REGISTERS = 2
  SSF_DETACH = 3
  SSF_SUSPEND = 4
  SSF_RESUME = 5
  SSF_READ_MEMORY = 6
  SSF_WRITE_MEMORY = 7
  SSF_TERMINATE = 8
  SSF_DEFINE_BREAKPOINT = 9
SF_FILE = 70
  SSF_READ_FILE = 0
  SSF_READ_FOLDER = 1
  SSF_CREATE_FILE = 2
  SSF_WRITE_FILE = 3
  SSF_SET_END = 4
  SSF_GET_INFO = 5
  SSF_SET_INFO = 6
  SSF_START_APP = 7
  SSF_DELETE = 8
  SSF_CREATE_FOLDER = 9
SF_SET_CAPTION = 71
SF_SEND_MESSAGE = 72
SF_BLITTER = 73
SF_NETWORK_DEVICE = 74
  SSF_DEVICE_COUNT = 255
  SSF_DEVICE_TYPE = 0
  SSF_DEVICE_NAME = 1
  SSF_RESET_DEVICE = 2
  SSF_STOP_DEVICE = 3
  SSF_DEVICE_POINTER = 4
  SSF_TX_PACKET_COUNT = 6
  SSF_RX_PACKET_COUNT = 7
  SSF_TX_BYTE_COUNT = 8
  SSF_RX_BYTE_COUNT = 9
  SSF_LINK_STATUS = 10
  SSF_TX_PACKET_ERROR_COUNT = 11
  SSF_TX_PACKET_DROP_COUNT = 12
  SSF_TX_PACKET_MISS_COUNT = 13
  SSF_RX_PACKET_ERROR_COUNT = 14
  SSF_RX_PACKET_DROP_COUNT = 15
  SSF_RX_PACKET_MISS_COUNT = 16
SF_NETWORK_SOCKET = 75
  SSF_OPEN = 0
  SSF_CLOSE = 1
  SSF_BIND = 2
  SSF_LISTEN = 3
  SSF_CONNECT = 4
  SSF_ACCEPT = 5
  SSF_SEND = 6
  SSF_RECEIVE = 7
  SSF_SET_OPTIONS = 8
  SSF_GET_OPTIONS = 9
  SSF_SOCKET_PAIR = 10
SF_NETWORK_PROTOCOL = 76
  SSF_ETHERNET_READ_MAC = 0
  SSF_IP4_PACKETS_SENT = 10000h
  SSF_IP4_PACKETS_RECEIVED = 10001h
  SSF_IP4_READ_IP = 10002h
  SSF_IP4_WRITE_IP = 10003h
  SSF_IP4_READ_DNS = 10004h
  SSF_IP4_WRITE_DNS = 10005h
  SSF_IP4_READ_SUBNET = 10006h
  SSF_IP4_WRITE_SUBNET = 10007h
  SSF_IP4_READ_GATEWAY = 10008h
  SSF_IP4_WRITE_GATEWAY = 10009h
  SSF_ICMP_PACKETS_SENT = 20000h
  SSF_ICMP_PACKETS_RECEIVED = 20001h
  SSF_ICMP_ECHO_REPLY = 20003h
  SSF_UDP_PACKETS_SENT = 30000h
  SSF_UDP_PACKETS_RECEIVED = 30001h
  SSF_TCP_PACKETS_SENT = 40000h
  SSF_TCP_PACKETS_RECEIVED = 40001h
  SSF_ARP_PACKETS_SENT = 50000h
  SSF_ARP_PACKETS_RECEIVED = 50001h
  SSF_ARP_GET_ENTRY_COUNT = 50002h
  SSF_ARP_READ_ENTRY = 50003h
  SSF_ARP_ADD_STATIC_ENTRY = 50004h
  SSF_ARP_DEL_ENTRY = 50005h
  SSF_ARP_SEND_ANNOUNCE = 50006h
  SSF_ARP_CONFLICTS_COUNT = 50007h
SF_FUTEX = 77
  SSF_CREATE = 0
  SSF_DESTROY = 1
  SSF_WAIT = 2
  SSF_WAKE = 3

;------------------- Error codes --------------------;

; KolibriOS-NG specific error codes:
ENOERR  = 0
EUNKFS  = 3
EEOF    = 6
EBADFS  = 9
EMPROCS = 32

; POSIX error codes:
ENOTSUP         = 2
ENOENT          = 5
EFAULT          = 7
ENOSPC          = 8
EACCES          = 10
EIO             = 11
EMSGSIZE        = 12
EBADF           = 13
EPIPE           = 14
EALREADY        = 15
EADDRINUSE      = 20
EADDRNOTAVAIL   = 21
ENFILE          = 23
ENOMEM          = 30
ENOEXEC         = 31
EINVAL          = 33
ENOBUFS         = 40
EINPROGRESS     = 41
EOPNOTSUPP      = 42
EWOULDBLOCK     = 43
ENOTCONN        = 44
ECONNRESET      = 52
ECONNABORTED    = 53
EISCONN         = 56
ETIMEDOUT       = 60
ECONNREFUSED    = 61

;---------------------- Events ----------------------;

KOS_EV_NONE       = 0
KOS_EV_REDRAW     = 1
KOS_EV_KEY        = 2
KOS_EV_BUTTON     = 3
KOS_EV_BACKGROUND = 5
KOS_EV_MOUSE      = 6
KOS_EV_IPC        = 7
KOS_EV_NETWORK    = 8 
KOS_EV_DEBUG      = 9
KOS_EV_IRQ_FIRST  = 16
KOS_EV_IRQ_LAST   = 31

;-------------------- Structures --------------------;

include 'struct.inc'

struct KOS_THREAD_INFO_S
  cpu_usage     dd ?  ;+0
  win_stack_pos dw ?  ;+4
  slot_num      dw ?  ;+6
                dw ?  ;+8   reserved
  name          rb 11 ;+10
                db ?  ;+21  reserved
  addr          dd ?  ;+22
  used_mem      dd ?  ;+26
  tid           dd ?  ;+30
  win_x         dd ?  ;+34
  win_y         dd ?  ;+38
  win_w         dd ?  ;+42
  win_h         dd ?  ;+46
  state         dw ?  ;+50
                dw ?  ;+52  reserved
  cli_x         dd ?  ;+54
  cli_y         dd ?  ;+58
  cli_w         dd ?  ;+62
  cli_h         dd ?  ;+66
  win_state     db ?  ;+70
  event_mask    dd ?  ;+71
  keyboard_mode db ?  ;+75
                rb (1024-$)
ends

assert sizeof.KOS_THREAD_INFO_S = 1024

struct KOS_SYS_COLORS_S
                   dd ? ;+0 reserved
                   dd ? ;+4 reserved
  work_dark        dd ? ;+8
  work_light       dd ? ;+12
  grab_text        dd ? ;+16
  work             dd ? ;+20
  work_button      dd ? ;+24
  work_button_text dd ? ;+28
  work_text        dd ? ;+32
  work_graph       dd ? ;+36
ends

assert sizeof.KOS_SYS_COLORS_S = 40

;-----------------  Helper macros -------------------;

macro mpack dest, hsrc, lsrc
{
  if (hsrc eqtype 0) & (lsrc eqtype 0)
    mov dest, (hsrc) shl 16 + lsrc
  else
    if (hsrc eqtype 0) & (~lsrc eqtype 0)
      mov dest, (hsrc) shl 16
      add dest, lsrc
    else
      mov dest, hsrc
      shl dest, 16
      add dest, lsrc
    end if
  end if
}

macro __mov reg,a,b {
  if (~a eq)&(~b eq)
    mpack reg,a,b
  else if (~a eq)&(b eq)
    mov reg,a
  end if
}

macro mcall a,b,c,d,e,f,g {
  __mov eax,a
  __mov ebx,b
  __mov ecx,c
  __mov edx,d
  __mov esi,e
  __mov edi,f
  __mov ebp,g
  int 0x40
}
