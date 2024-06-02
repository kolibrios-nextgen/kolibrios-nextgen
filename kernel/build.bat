:: Copyright (C) KolibriOS team 2018. All rights reserved
:: Copyright (C) KolibriOS-NG team 2024. All rights reserved
:: Distributed under terms of the GNU General Public License

@echo off
cls

call :Target_kernel

if ERRORLEVEL 0 goto Exit_OK

echo There was an error executing script.
echo For any help, please send a report.
pause
goto :eof

:Target_kernel
   :: Valid languages: en ru ge et sp
   set lang=en

   echo Building kernel with language '%lang%' ...
   echo lang fix %lang% > lang.inc

   fasm -m 262144 kernel.asm kernel.mnt
   fasm -m 262144 -dextended_primary_loader=1 kernel.asm kernel.mnt.ext_loader
   if not %errorlevel%==0 goto :Error_FasmFailed
goto :eof

:Error_FasmFailed
echo Error: fasm execution failed!
erase lang.inc >nul 2>&1
echo.
pause
exit 1

:Exit_OK
echo.
echo All operations have been done
pause
exit 0
