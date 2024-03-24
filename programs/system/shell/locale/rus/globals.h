/* WARNING: SAVE ONLY IN CP866 ENCODING! */

const command_t COMMANDS[]=
{
        {"about",   "  �뢮��� ���ଠ�� � �ணࠬ�� Shell\n\r", &cmd_about},
        {"alias",   "  �����뢠�� � �������� �������� ᯨ᮪ ᨭ������ ������\n\r", &cmd_alias},
        {"cd",      "  ������� ⥪���� ��ਪ���. �ᯮ�짮�����:\n\r    cd <��४���>\n\r", &cmd_cd},
        {"clear",   "  ��頥� ��࠭\n\r", &cmd_clear},
        {"cp",      "  ������� 䠩�\n\r", &cmd_cp},
        {"mv",      "  ��६�頥� 䠩�\n\r", &cmd_mv},
        {"ren",     "  ��२�����뢠�� 䠩�\n\r", &cmd_ren},
        {"date",    "  �����뢠�� ⥪���� ���� � �६�\n\r", &cmd_date},
        {"echo",    "  �뢮��� ����� �� ��࠭. �ᯮ�짮�����:\n\r    echo <�����>\n\r", &cmd_echo},
        {"exit",    "  �����襭�� ࠡ��� Shell\n\r", &cmd_exit},
        {"free",    "  �����뢠�� ���� ����⨢��� �����: �ᥩ, ᢮������ � �ᯮ��㥬��\n\r", &cmd_memory},
        {"help",    "  ��ࠢ�� �� ��������. �ᯮ�짮�����:\n\r    help ;ᯨ᮪ ��� ������\n\r    help <�������> ;�ࠢ�� �� �������\n\r", &cmd_help},
        {"history", "  ���᮪ �ᯮ�짮������ ������\n\r", &cmd_history},   
		{"kfetch",  "  ���⠥� ���� � ���ଠ�� � ��⥬�.\n\r", &cmd_kfetch},    
        {"kill",    "  ������� �����. �ᯮ�짮�����:\n\r    kill <PID �����>\n\r    kill all\n\r", &cmd_kill},
        {"pkill",   "  ������� �� ������ �� �����. �ᯮ�짮�����:\n\r    pkill <���_�����>\n\r", &cmd_pkill},
        {"ls",      "  �뢮��� ᯨ᮪ 䠩���. �ᯮ�짮�����:\n\r    ls ;ᯨ᮪ 䠩��� � ⥪�饬 ��⠫���\n\r    ls <��४���> ;ᯨ᮪ 䠩��� �� �������� ��४�ਨ\n\r", &cmd_ls},
        {"lsmod",	"  list working driver \n\r", &cmd_lsmod},
		{"mkdir",   "  ������� ��⠫�� � த�⥫�᪨� ��⠫��� �� ����室�����. �ᯮ�짮�����:\n\r    mkdir <���/�����>", &cmd_mkdir},
        {"more",    "  �뢮��� ᮤ�ন��� 䠩�� �� ��࠭. �ᯮ�짮�����:\n\r    more <��� 䠩��>\n\r", &cmd_more},
        {"ps",      "  �뢮��� ᯨ᮪ ����ᮢ\n\r  �᫨ 㪠���� <�������>, �����뢠�� ����� ������ � ��࠭�� LASTPID\n\r", &cmd_ps},
        {"pwd",     "  �����뢠�� ��� ⥪�饩 ��४�ਨ\n\r", &cmd_pwd},
        {"reboot",  "  ��१���㦠�� �������� ��� �� KolibriOS. �ᯮ�짮�����:\n\r    reboot ;��१���㧨�� ��\n\r    reboot kernel ;��१������� �� Kolibri\n\r", &cmd_reboot},
        {"rm",      "  ������ 䠩�. �ᯮ�짮�����:\n\r    rm <��� 䠩��>\n\r", &cmd_rm},
        {"rmdir",   "  ������ �����. �ᯮ�짮�����:\n\r    rmdir <��४���>\n\r", &cmd_rmdir},
        {"shutdown","  �몫�砥� ��������\n\r", &cmd_shutdown},
        {"sleep",   "  ��⠭�������� ࠡ��� Shell'� �� �������� �६�. �ᯮ�짮�����:\n\r    sleep <���ࢠ� � ���� ���� ᥪ㭤�>\n\r  �ਬ��:\n\r    sleep 500 ;��㧠 �� 5 ᥪ.\n\r", &cmd_sleep},
        {"touch",   "  ������� ���⮩ 䠩� ��� ������� ����/�६� ᮧ����� 䠩��. �ᯮ�짮�����:\n\r    touch <��� 䠩��>\n\r", &cmd_touch},
        {"uptime",  "  �����뢠�� uptime\n\r", &cmd_uptime},
        {"ver",     "  �����뢠�� �����. �ᯮ�짮�����:\n\r    ver ;����� Shell\n\r    ver kernel ;����� � ����� ॢ���� �� KolibriOS\n\r    ver cpu ;���ଠ�� � ������\n\r", &cmd_ver},
        {"waitfor", "  �ਮ�⠭�������� �믮������ ������. �ᯮ�짮�����:\n\r    waitfor ;������� �।��騩 ����饭�� ����� LASTPID\n\r    waitfor <PID>;���� �����襭�� ����� � 㪠����� PID\n\r", &cmd_waitfor},
};

#define CMD_ABOUT_MSG "Shell %s\n\r"
#define CMD_CD_USAGE "  cd <��४���>\n\r"
#define CMD_CP_USAGE "  cp <���筨�> <१����>\n\r"
#define CMD_DATE_DATE_FMT "  ��� [��.��.��]: %x%x.%x%x.%x%x"
#define CMD_DATE_TIME_FMT "\n\r  �६� [��:��:��]: %x%x:%x%x:%x%x\n\r"
#define CMD_FREE_FMT "  �ᥣ�        [�� / �� / %%]:  %-7d / %-5d / 100\n\r  ��������     [�� / �� / %%]:  %-7d / %-5d / %d\n\r  �ᯮ������ [�� / �� / %%]:  %-7d / %-5d / %d\n\r"
#define CMD_HELP_AVAIL "  ������⢮ ����㯭�� ������: %d\n\r"
#define CMD_HELP_CMD_NOT_FOUND "  ������� \'%s\' �� �������.\n\r"

#define CMD_KILL_USAGE "  kill <PID>\n\r"
#define CMD_MKDIR_USAGE "  mkdir <��४���>\n\r"
#define CMD_MORE_USAGE "  more <��� 䠩��>\n\r"
#define CMD_MV_USAGE "  mv <���筨�> <१����>\n\r"
#define CMD_PKILL_HELP      "  pkill <��� �����>\n\r"
#define CMD_PKILL_KILL      "  PID: %u - 㡨�\n"
#define CMD_PKILL_NOT_KILL  "  PID: %u - �� 㡨�\n"
#define CMD_PKILL_NOT_FOUND "  ����ᮢ � ⠪�� ������ �� �������!\n"

#define CMD_REN_USAGE "  ren <䠩�> <����� ���>\n\r"
#define CMD_RM_USAGE "  rm <��� 䠩��>\n\r"
#define CMD_RMDIR_USAGE "  rmdir <��४���>\n\r"
#define CMD_SLEEP_USAGE "  sleep <���ࢠ� � ���� ����x ᥪ㭤�>\n\r"
#define CMD_TOUCH_USAGE "  touch <��� 䠩��>\n\r"
#define CMD_UPTIME_FMT "  Uptime: %d ����, %d:%d:%d.%d\n\r"
#define CMD_VER_FMT1 "  KolibriOS-NG v%d.%d.%d-%d-%s\n\r"
#define CMD_WAITFOR_FMT "  ������� �����襭�� PID %d\n\r"
#define EXEC_STARTED_FMT "  '%s' ����饭. PID = %d\n\r"
#define EXEC_SCRIPT_ERROR_FMT "�訡�� � '%s' : �ਯ� ������ ��稭����� � ���窨 #SHS\n\r"
#define UNKNOWN_CMD_ERROR "  �訡��!\n\r"
#define CON_APP_ERROR "  �訡�� � ���᮫쭮� �ਫ������.\n\r"
#define FILE_NOT_FOUND_ERROR "  ���� '%s' �� ������.\n\r"
