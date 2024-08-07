import libc,\
    __Balloc,'_Balloc',\
    __Bfree,'_Bfree',\
    __Exit,'_Exit',\
    ___ChkTTYIOMode,'__ChkTTYIOMode',\
    ___GetIOMode,'__GetIOMode',\
    ___SetIOMode,'__SetIOMode',\
    ___SetIOMode_nogrow,'__SetIOMode_nogrow',\
    ___allocPOSIXHandle,'__allocPOSIXHandle',\
    ___any_on,'__any_on',\
    ___ascii_mbtowc,'__ascii_mbtowc',\
    ___ascii_wctomb,'__ascii_wctomb',\
    ___assert_func,'__assert_func',\
    ___b2d,'__b2d',\
    ___call_exitprocs,'__call_exitprocs',\
    ___copybits,'__copybits',\
    ___cpu_features_init,'__cpu_features_init',\
    ___ctype_load_locale,'__ctype_load_locale',\
    ___ctype_ptr__,'__ctype_ptr__',\
    ___d2b,'__d2b',\
    ___dorand48,'__dorand48',\
    ___dtoa,'__dtoa',\
    ___emutls_get_address,'__emutls_get_address',\
    ___emutls_register_common,'__emutls_register_common',\
    ___errno,'__errno',\
    ___fp_lock_all,'__fp_lock_all',\
    ___fp_unlock_all,'__fp_unlock_all',\
    ___fpclassifyd,'__fpclassifyd',\
    ___fpclassifyf,'__fpclassifyf',\
    ___freePOSIXHandle,'__freePOSIXHandle',\
    ___getOSHandle,'__getOSHandle',\
    ___get_current_ctype_locale,'__get_current_ctype_locale',\
    ___gethex,'__gethex',\
    ___gettzinfo,'__gettzinfo',\
    ___growPOSIXHandles,'__growPOSIXHandles',\
    ___grow_iomode,'__grow_iomode',\
    ___gthread_once,'__gthread_once',\
    ___hexdig_init,'__hexdig_init',\
    ___hexnan,'__hexnan',\
    ___hi0bits,'__hi0bits',\
    ___i2b,'__i2b',\
    ___ieee754_acos,'__ieee754_acos',\
    ___ieee754_acosf,'__ieee754_acosf',\
    ___ieee754_acosh,'__ieee754_acosh',\
    ___ieee754_acoshf,'__ieee754_acoshf',\
    ___ieee754_asin,'__ieee754_asin',\
    ___ieee754_asinf,'__ieee754_asinf',\
    ___ieee754_atan2,'__ieee754_atan2',\
    ___ieee754_atan2f,'__ieee754_atan2f',\
    ___ieee754_atanh,'__ieee754_atanh',\
    ___ieee754_atanhf,'__ieee754_atanhf',\
    ___ieee754_cosh,'__ieee754_cosh',\
    ___ieee754_coshf,'__ieee754_coshf',\
    ___ieee754_exp,'__ieee754_exp',\
    ___ieee754_expf,'__ieee754_expf',\
    ___ieee754_fmod,'__ieee754_fmod',\
    ___ieee754_fmodf,'__ieee754_fmodf',\
    ___ieee754_gamma_r,'__ieee754_gamma_r',\
    ___ieee754_gammaf_r,'__ieee754_gammaf_r',\
    ___ieee754_hypot,'__ieee754_hypot',\
    ___ieee754_hypotf,'__ieee754_hypotf',\
    ___ieee754_j0,'__ieee754_j0',\
    ___ieee754_j0f,'__ieee754_j0f',\
    ___ieee754_j1,'__ieee754_j1',\
    ___ieee754_j1f,'__ieee754_j1f',\
    ___ieee754_jn,'__ieee754_jn',\
    ___ieee754_jnf,'__ieee754_jnf',\
    ___ieee754_lgamma_r,'__ieee754_lgamma_r',\
    ___ieee754_lgammaf_r,'__ieee754_lgammaf_r',\
    ___ieee754_log,'__ieee754_log',\
    ___ieee754_log10,'__ieee754_log10',\
    ___ieee754_log10f,'__ieee754_log10f',\
    ___ieee754_logf,'__ieee754_logf',\
    ___ieee754_pow,'__ieee754_pow',\
    ___ieee754_powf,'__ieee754_powf',\
    ___ieee754_rem_pio2,'__ieee754_rem_pio2',\
    ___ieee754_rem_pio2f,'__ieee754_rem_pio2f',\
    ___ieee754_remainder,'__ieee754_remainder',\
    ___ieee754_remainderf,'__ieee754_remainderf',\
    ___ieee754_scalb,'__ieee754_scalb',\
    ___ieee754_scalbf,'__ieee754_scalbf',\
    ___ieee754_sinh,'__ieee754_sinh',\
    ___ieee754_sinhf,'__ieee754_sinhf',\
    ___ieee754_sqrt,'__ieee754_sqrt',\
    ___ieee754_sqrtf,'__ieee754_sqrtf',\
    ___ieee754_y0,'__ieee754_y0',\
    ___ieee754_y0f,'__ieee754_y0f',\
    ___ieee754_y1,'__ieee754_y1',\
    ___ieee754_y1f,'__ieee754_y1f',\
    ___ieee754_yn,'__ieee754_yn',\
    ___ieee754_ynf,'__ieee754_ynf',\
    ___infinity,'__infinity',\
    ___infinityf,'__infinityf',\
    ___infinityld,'__infinityld',\
    ___init_mode,'__init_mode',\
    ___io_mode,'__io_mode',\
    ___isinfd,'__isinfd',\
    ___isinff,'__isinff',\
    ___isnand,'__isnand',\
    ___isnanf,'__isnanf',\
    ___kernel_cos,'__kernel_cos',\
    ___kernel_cosf,'__kernel_cosf',\
    ___kernel_rem_pio2,'__kernel_rem_pio2',\
    ___kernel_rem_pio2f,'__kernel_rem_pio2f',\
    ___kernel_sin,'__kernel_sin',\
    ___kernel_sinf,'__kernel_sinf',\
    ___kernel_standard,'__kernel_standard',\
    ___kernel_tan,'__kernel_tan',\
    ___kernel_tanf,'__kernel_tanf',\
    ___libc_getenv,'__libc_getenv',\
    ___lo0bits,'__lo0bits',\
    ___locale_charset,'__locale_charset',\
    ___locale_cjk_lang,'__locale_cjk_lang',\
    ___locale_mb_cur_max,'__locale_mb_cur_max',\
    ___locale_msgcharset,'__locale_msgcharset',\
    ___lshift,'__lshift',\
    ___malloc_lock,'__malloc_lock',\
    ___malloc_unlock,'__malloc_unlock',\
    ___mb_cur_max,'__mb_cur_max',\
    ___mbtowc,'__mbtowc',\
    ___mcmp,'__mcmp',\
    ___mdiff,'__mdiff',\
    ___mlocale_changed,'__mlocale_changed',\
    ___mprec_bigtens,'__mprec_bigtens',\
    ___mprec_tens,'__mprec_tens',\
    ___mprec_tinytens,'__mprec_tinytens',\
    ___multadd,'__multadd',\
    ___multiply,'__multiply',\
    ___mutex_lock,'__mutex_lock',\
    ___nlocale_changed,'__nlocale_changed',\
    ___pow5mult,'__pow5mult',\
    ___ratio,'__ratio',\
    ___register_exitproc,'__register_exitproc',\
    ___s2b,'__s2b',\
    ___sccl,'__sccl',\
    ___sclose,'__sclose',\
    ___seofread,'__seofread',\
    ___setOSHandle,'__setOSHandle',\
    ___set_handles,'__set_handles',\
    ___sflags,'__sflags',\
    ___sflush_r,'__sflush_r',\
    ___sfmoreglue,'__sfmoreglue',\
    ___sfp,'__sfp',\
    ___sfp_lock_acquire,'__sfp_lock_acquire',\
    ___sfp_lock_release,'__sfp_lock_release',\
    ___sfvwrite_r,'__sfvwrite_r',\
    ___shrink_iomode,'__shrink_iomode',\
    ___signbitd,'__signbitd',\
    ___signbitf,'__signbitf',\
    ___sigtramp,'__sigtramp',\
    ___sigtramp_r,'__sigtramp_r',\
    ___sinit,'__sinit',\
    ___sinit_lock_acquire,'__sinit_lock_acquire',\
    ___sinit_lock_release,'__sinit_lock_release',\
    ___smakebuf_r,'__smakebuf_r',\
    ___sprint_r,'__sprint_r',\
    ___sread,'__sread',\
    ___srefill_r,'__srefill_r',\
    ___srget,'__srget',\
    ___srget_r,'__srget_r',\
    ___sseek,'__sseek',\
    ___ssprint_r,'__ssprint_r',\
    ___ssrefill_r,'__ssrefill_r',\
    ___ssvfiscanf_r,'__ssvfiscanf_r',\
    ___ssvfscanf_r,'__ssvfscanf_r',\
    ___strtok_r,'__strtok_r',\
    ___submore,'__submore',\
    ___svfiscanf,'__svfiscanf',\
    ___svfiscanf_r,'__svfiscanf_r',\
    ___svfscanf,'__svfscanf',\
    ___svfscanf_r,'__svfscanf_r',\
    ___swbuf,'__swbuf',\
    ___swbuf_r,'__swbuf_r',\
    ___swrite,'__swrite',\
    ___swsetup_r,'__swsetup_r',\
    ___thread_startup,'__thread_startup',\
    ___tz_lock,'__tz_lock',\
    ___tz_unlock,'__tz_unlock',\
    ___tzcalc_limits,'__tzcalc_limits',\
    ___ulp,'__ulp',\
    ___wctomb,'__wctomb',\
    __assert,'_assert',\
    __atoi_r,'_atoi_r',\
    __atol_r,'_atol_r',\
    __buf_findstr,'_buf_findstr',\
    __calloc_r,'_calloc_r',\
    __cleanup,'_cleanup',\
    __cleanup_r,'_cleanup_r',\
    __close_r,'_close_r',\
    __ctype_,'_ctype_',\
    __daylight,'_daylight',\
    __diprintf_r,'_diprintf_r',\
    __dprintf_r,'_dprintf_r',\
    __dtoa_r,'_dtoa_r',\
    __exit,'_exit',\
    __f_atan2,'_f_atan2',\
    __f_atan2f,'_f_atan2f',\
    __f_exp,'_f_exp',\
    __f_expf,'_f_expf',\
    __f_frexp,'_f_frexp',\
    __f_frexpf,'_f_frexpf',\
    __f_ldexp,'_f_ldexp',\
    __f_ldexpf,'_f_ldexpf',\
    __f_llrint,'_f_llrint',\
    __f_llrintf,'_f_llrintf',\
    __f_llrintl,'_f_llrintl',\
    __f_log,'_f_log',\
    __f_log10,'_f_log10',\
    __f_log10f,'_f_log10f',\
    __f_logf,'_f_logf',\
    __f_lrint,'_f_lrint',\
    __f_lrintf,'_f_lrintf',\
    __f_lrintl,'_f_lrintl',\
    __f_pow,'_f_pow',\
    __f_powf,'_f_powf',\
    __f_rint,'_f_rint',\
    __f_rintf,'_f_rintf',\
    __f_rintl,'_f_rintl',\
    __f_tan,'_f_tan',\
    __f_tanf,'_f_tanf',\
    __fclose_r,'_fclose_r',\
    __fdopen_r,'_fdopen_r',\
    __fflush_r,'_fflush_r',\
    __fgetc_r,'_fgetc_r',\
    __fgets_r,'_fgets_r',\
    __findenv,'_findenv',\
    __fiprintf_r,'_fiprintf_r',\
    __fiscanf_r,'_fiscanf_r',\
    __fopen_r,'_fopen_r',\
    __fprintf_r,'_fprintf_r',\
    __fputc_r,'_fputc_r',\
    __fputs_r,'_fputs_r',\
    __fputwc_r,'_fputwc_r',\
    __fread_r,'_fread_r',\
    __free_r,'_free_r',\
    __freopen_r,'_freopen_r',\
    __fscanf_r,'_fscanf_r',\
    __fseek_r,'_fseek_r',\
    __fseeko_r,'_fseeko_r',\
    __fstat_r,'_fstat_r',\
    __ftell_r,'_ftell_r',\
    __ftello_r,'_ftello_r',\
    __fwalk,'_fwalk',\
    __fwalk_reent,'_fwalk_reent',\
    __fwrite_r,'_fwrite_r',\
    __gettimeofday,'_gettimeofday',\
    __gettimeofday_r,'_gettimeofday_r',\
    __global_impure_ptr,'_global_impure_ptr',\
    __grow_handles,'_grow_handles',\
    __init_signal,'_init_signal',\
    __init_signal_r,'_init_signal_r',\
    __isatty,'_isatty',\
    __isatty_r,'_isatty_r',\
    __kill_r,'_kill_r',\
    __localeconv_r,'_localeconv_r',\
    __lseek_r,'_lseek_r',\
    __malloc_r,'_malloc_r',\
    __mbrtowc_r,'_mbrtowc_r',\
    __mbtowc_r,'_mbtowc_r',\
    __mktm_r,'_mktm_r',\
    __mprec_log10,'_mprec_log10',\
    __open_r,'_open_r',\
    __printf_r,'_printf_r',\
    __putc_r,'_putc_r',\
    __putchar_r,'_putchar_r',\
    __puts_r,'_puts_r',\
    __raise_r,'_raise_r',\
    __read,'_read',\
    __read_r,'_read_r',\
    __realloc_r,'_realloc_r',\
    __remove_r,'_remove_r',\
    __rename_r,'_rename_r',\
    __seed48_r,'_seed48_r',\
    __setlocale_r,'_setlocale_r',\
    __sfread_r,'_sfread_r',\
    __signal_r,'_signal_r',\
    __siprintf_r,'_siprintf_r',\
    __sniprintf_r,'_sniprintf_r',\
    __snprintf_r,'_snprintf_r',\
    __sprintf_r,'_sprintf_r',\
    __srand48_r,'_srand48_r',\
    __sscanf_r,'_sscanf_r',\
    __strdup_r,'_strdup_r',\
    __strerror_r,'_strerror_r',\
    __strndup_r,'_strndup_r',\
    __strtod_r,'_strtod_r',\
    __strtol_r,'_strtol_r',\
    __strtoll_r,'_strtoll_r',\
    __strtoul_r,'_strtoul_r',\
    __strtoull_r,'_strtoull_r',\
    __sungetc_r,'_sungetc_r',\
    __svfiprintf_r,'_svfiprintf_r',\
    __svfprintf_r,'_svfprintf_r',\
    __system_r,'_system_r',\
    __tempnam_r,'_tempnam_r',\
    __times_r,'_times_r',\
    __timezone,'_timezone',\
    __tls_map,'_tls_map',\
    __tmpfile_r,'_tmpfile_r',\
    __tmpnam_r,'_tmpnam_r',\
    __towctrans_r,'_towctrans_r',\
    __tzname,'_tzname',\
    __ungetc_r,'_ungetc_r',\
    __user_strerror,'_user_strerror',\
    __vasniprintf_r,'_vasniprintf_r',\
    __vasnprintf_r,'_vasnprintf_r',\
    __vdiprintf_r,'_vdiprintf_r',\
    __vdprintf_r,'_vdprintf_r',\
    __vfiprintf_r,'_vfiprintf_r',\
    __vfiscanf_r,'_vfiscanf_r',\
    __vfprintf_r,'_vfprintf_r',\
    __vfscanf_r,'_vfscanf_r',\
    __vscanf_r,'_vscanf_r',\
    __vsnprintf_r,'_vsnprintf_r',\
    __vsprintf_r,'_vsprintf_r',\
    __vsscanf_r,'_vsscanf_r',\
    __wcrtomb_r,'_wcrtomb_r',\
    __wctomb_r,'_wctomb_r',\
    __wctrans_r,'_wctrans_r',\
    __wctype_r,'_wctype_r',\
    __write_r,'_write_r',\
    _abort,'abort',\
    _abs,'abs',\
    _acos,'acos',\
    _acosf,'acosf',\
    _acosh,'acosh',\
    _acoshf,'acoshf',\
    _asctime,'asctime',\
    _asctime_r,'asctime_r',\
    _asin,'asin',\
    _asinf,'asinf',\
    _asinh,'asinh',\
    _asinhf,'asinhf',\
    _atan,'atan',\
    _atan2,'atan2',\
    _atan2f,'atan2f',\
    _atanf,'atanf',\
    _atanh,'atanh',\
    _atanhf,'atanhf',\
    _atof,'atof',\
    _atoi,'atoi',\
    _atol,'atol',\
    _bsearch,'bsearch',\
    _calloc,'calloc',\
    _cbrt,'cbrt',\
    _cbrtf,'cbrtf',\
    _ceil,'ceil',\
    _ceilf,'ceilf',\
    _clearerr,'clearerr',\
    _clock,'clock',\
    _close,'close',\
    _copysign,'copysign',\
    _copysignf,'copysignf',\
    _cos,'cos',\
    _cosf,'cosf',\
    _cosh,'cosh',\
    _coshf,'coshf',\
    _create_image,'create_image',\
    _create_thread,'create_thread',\
    _ctime,'ctime',\
    _ctime_r,'ctime_r',\
    _debugwrite,'debugwrite',\
    _delete_file,'delete_file',\
    _difftime,'difftime',\
    _diprintf,'diprintf',\
    _div,'div',\
    _dprintf,'dprintf',\
    _drem,'drem',\
    _dremf,'dremf',\
    _entry,'entry',\
    _envz_get,'envz_get',\
    _erf,'erf',\
    _erfc,'erfc',\
    _erfcf,'erfcf',\
    _erff,'erff',\
    _exit,'exit',\
    _exp,'exp',\
    _exp10,'exp10',\
    _exp10f,'exp10f',\
    _exp2,'exp2',\
    _exp2f,'exp2f',\
    _expf,'expf',\
    _expm1,'expm1',\
    _expm1f,'expm1f',\
    _fabs,'fabs',\
    _fabsf,'fabsf',\
    _fclose,'fclose',\
    _fdim,'fdim',\
    _fdimf,'fdimf',\
    _fdopen,'fdopen',\
    _fflush,'fflush',\
    _fgetc,'fgetc',\
    _fgets,'fgets',\
    _fileno,'fileno',\
    _finite,'finite',\
    _finitef,'finitef',\
    _fiprintf,'fiprintf',\
    _fiscanf,'fiscanf',\
    _floor,'floor',\
    _floorf,'floorf',\
    _fma,'fma',\
    _fmaf,'fmaf',\
    _fmax,'fmax',\
    _fmaxf,'fmaxf',\
    _fmin,'fmin',\
    _fminf,'fminf',\
    _fmod,'fmod',\
    _fmodf,'fmodf',\
    _fopen,'fopen',\
    _fprintf,'fprintf',\
    _fputc,'fputc',\
    _fputs,'fputs',\
    _fputwc,'fputwc',\
    _fread,'fread',\
    _free,'free',\
    _freopen,'freopen',\
    _frexp,'frexp',\
    _frexpf,'frexpf',\
    _fscanf,'fscanf',\
    _fseek,'fseek',\
    _fseeko,'fseeko',\
    _fstat,'fstat',\
    _ftell,'ftell',\
    _ftello,'ftello',\
    _fwrite,'fwrite',\
    _gamma,'gamma',\
    _gamma_r,'gamma_r',\
    _gammaf,'gammaf',\
    _gammaf_r,'gammaf_r',\
    _get_entry_point,'get_entry_point',\
    _get_proc_address,'get_proc_address',\
    _getenv,'getenv',\
    _gettimeofday,'gettimeofday',\
    _gmtime,'gmtime',\
    _gmtime_r,'gmtime_r',\
    _hypot,'hypot',\
    _hypotf,'hypotf',\
    _ilogb,'ilogb',\
    _ilogbf,'ilogbf',\
    _infinity,'infinity',\
    _infinityf,'infinityf',\
    _init_global_reent,'init_global_reent',\
    _init_loader,'init_loader',\
    _init_reent,'init_reent',\
    _isalnum,'isalnum',\
    _isalpha,'isalpha',\
    _isascii,'isascii',\
    _isblank,'isblank',\
    _iscntrl,'iscntrl',\
    _isdigit,'isdigit',\
    _isgraph,'isgraph',\
    _isinf,'isinf',\
    _isinff,'isinff',\
    _islower,'islower',\
    _isnan,'isnan',\
    _isnanf,'isnanf',\
    _isprint,'isprint',\
    _ispunct,'ispunct',\
    _isspace,'isspace',\
    _isupper,'isupper',\
    _iswalnum,'iswalnum',\
    _iswalpha,'iswalpha',\
    _iswblank,'iswblank',\
    _iswcntrl,'iswcntrl',\
    _iswctype,'iswctype',\
    _iswdigit,'iswdigit',\
    _iswgraph,'iswgraph',\
    _iswlower,'iswlower',\
    _iswprint,'iswprint',\
    _iswpunct,'iswpunct',\
    _iswspace,'iswspace',\
    _iswupper,'iswupper',\
    _iswxdigit,'iswxdigit',\
    _isxdigit,'isxdigit',\
    _j0,'j0',\
    _j0f,'j0f',\
    _j1,'j1',\
    _j1f,'j1f',\
    _jn,'jn',\
    _jnf,'jnf',\
    _ldexp,'ldexp',\
    _ldexpf,'ldexpf',\
    _lgamma,'lgamma',\
    _lgamma_r,'lgamma_r',\
    _lgammaf,'lgammaf',\
    _lgammaf_r,'lgammaf_r',\
    _libc_crt_startup,'libc_crt_startup',\
    _link_app,'link_app',\
    _link_image,'link_image',\
    _llrint,'llrint',\
    _llrintf,'llrintf',\
    _llrintl,'llrintl',\
    _llround,'llround',\
    _llroundf,'llroundf',\
    _load_library,'load_library',\
    _loader_env,'loader_env',\
    _localeconv,'localeconv',\
    _localtime,'localtime',\
    _localtime_r,'localtime_r',\
    _log,'log',\
    _log10,'log10',\
    _log10f,'log10f',\
    _log1p,'log1p',\
    _log1pf,'log1pf',\
    _log2,'log2',\
    _log2f,'log2f',\
    _logb,'logb',\
    _logbf,'logbf',\
    _logf,'logf',\
    _longjmp,'longjmp',\
    _lrint,'lrint',\
    _lrintf,'lrintf',\
    _lrintl,'lrintl',\
    _lround,'lround',\
    _lroundf,'lroundf',\
    _lseek,'lseek',\
    _malloc,'malloc',\
    _matherr,'matherr',\
    _mbrtowc,'mbrtowc',\
    _mbtowc,'mbtowc',\
    _memalign,'memalign',\
    _memchr,'memchr',\
    _memcmp,'memcmp',\
    _memcpy,'memcpy',\
    _memmove,'memmove',\
    _memset,'memset',\
    _mktime,'mktime',\
    _modf,'modf',\
    _modff,'modff',\
    _nan,'nan',\
    _nanf,'nanf',\
    _nearbyint,'nearbyint',\
    _nearbyintf,'nearbyintf',\
    _nextafter,'nextafter',\
    _nextafterf,'nextafterf',\
    _open,'open',\
    _path_list,'path_list',\
    _pow,'pow',\
    _pow10,'pow10',\
    _pow10f,'pow10f',\
    _powf,'powf',\
    _printf,'printf',\
    _putc,'putc',\
    _putchar,'putchar',\
    _puts,'puts',\
    _qsort,'qsort',\
    _raise,'raise',\
    _rand,'rand',\
    _rand_r,'rand_r',\
    _read,'read',\
    _realloc,'realloc',\
    _remainder,'remainder',\
    _remainderf,'remainderf',\
    _remove,'remove',\
    _remquo,'remquo',\
    _remquof,'remquof',\
    _rename,'rename',\
    _rint,'rint',\
    _rintf,'rintf',\
    _rintl,'rintl',\
    _round,'round',\
    _roundf,'roundf',\
    _scalb,'scalb',\
    _scalbf,'scalbf',\
    _scalbln,'scalbln',\
    _scalblnf,'scalblnf',\
    _scalbn,'scalbn',\
    _scalbnf,'scalbnf',\
    _seed48,'seed48',\
    _setjmp,'setjmp',\
    _setlocale,'setlocale',\
    _setvbuf,'setvbuf',\
    _signal,'signal',\
    _significand,'significand',\
    _significandf,'significandf',\
    _sin,'sin',\
    _sincos,'sincos',\
    _sincosf,'sincosf',\
    _sinf,'sinf',\
    _sinh,'sinh',\
    _sinhf,'sinhf',\
    _siprintf,'siprintf',\
    _sniprintf,'sniprintf',\
    _snprintf,'snprintf',\
    _sprintf,'sprintf',\
    _sqrt,'sqrt',\
    _sqrtf,'sqrtf',\
    _srand,'srand',\
    _srand48,'srand48',\
    _sscanf,'sscanf',\
    _stpcpy,'stpcpy',\
    _stpncpy,'stpncpy',\
    _strcasecmp,'strcasecmp',\
    _strcasestr,'strcasestr',\
    _strcat,'strcat',\
    _strchr,'strchr',\
    _strcmp,'strcmp',\
    _strcoll,'strcoll',\
    _strcpy,'strcpy',\
    _strcspn,'strcspn',\
    _strdup,'strdup',\
    _strerror,'strerror',\
    _strftime,'strftime',\
    _strlen,'strlen',\
    _strncasecmp,'strncasecmp',\
    _strncat,'strncat',\
    _strncmp,'strncmp',\
    _strncpy,'strncpy',\
    _strndup,'strndup',\
    _strnlen,'strnlen',\
    _strpbrk,'strpbrk',\
    _strrchr,'strrchr',\
    _strsep,'strsep',\
    _strspn,'strspn',\
    _strstr,'strstr',\
    _strtod,'strtod',\
    _strtof,'strtof',\
    _strtok,'strtok',\
    _strtok_r,'strtok_r',\
    _strtol,'strtol',\
    _strtoll,'strtoll',\
    _strtoul,'strtoul',\
    _strtoull,'strtoull',\
    _strupr,'strupr',\
    _system,'system',\
    _tan,'tan',\
    _tanf,'tanf',\
    _tanh,'tanh',\
    _tanhf,'tanhf',\
    _tempnam,'tempnam',\
    _tgamma,'tgamma',\
    _tgammaf,'tgammaf',\
    _time,'time',\
    _tls_alloc,'tls_alloc',\
    _tmpfile,'tmpfile',\
    _tmpnam,'tmpnam',\
    _toascii,'toascii',\
    _tolower,'tolower',\
    _toupper,'toupper',\
    _towctrans,'towctrans',\
    _towlower,'towlower',\
    _towupper,'towupper',\
    _trunc,'trunc',\
    _truncf,'truncf',\
    _ungetc,'ungetc',\
    _user_alloc,'user_alloc',\
    _validate_pe,'validate_pe',\
    _vasniprintf,'vasniprintf',\
    _vasnprintf,'vasnprintf',\
    _vdiprintf,'vdiprintf',\
    _vdprintf,'vdprintf',\
    _vfiprintf,'vfiprintf',\
    _vfiscanf,'vfiscanf',\
    _vfprintf,'vfprintf',\
    _vfscanf,'vfscanf',\
    _vscanf,'vscanf',\
    _vsnprintf,'vsnprintf',\
    _vsprintf,'vsprintf',\
    _vsscanf,'vsscanf',\
    _wcrtomb,'wcrtomb',\
    _wctrans,'wctrans',\
    _wctype,'wctype',\
    _write,'write',\
    _y0,'y0',\
    _y0f,'y0f',\
    _y1,'y1',\
    _y1f,'y1f',\
    _yn,'yn',\
    _ynf,'ynf'
