@echo off
set OPT=/EHsc -I../ /W4 -D_CRT_SECURE_NO_WARNINGS
set TARGET=..\xbyak\xbyak_mnemonic.h
set SORT=.\sortline

python gen_avx_type_def.py ..\xbyak\xbyak.h avx_type_def.h
if errorlevel 1 goto ERR

cl sortline.cpp %OPT%
if errorlevel 1 goto ERR

cl gen_code.cpp %OPT%
if errorlevel 1 goto ERR

cl gen_avx512.cpp %OPT%
if errorlevel 1 goto ERR

cl gen_ace_1.cpp %OPT%
if errorlevel 1 goto ERR

.\gen_code | %SORT% > %TARGET%
echo #ifdef XBYAK_ENABLE_OMITTED_OPERAND>> %TARGET%
.\gen_code omit | %SORT% >> %TARGET%
echo #endif>>%TARGET%
.\gen_code fixed >> %TARGET%
echo #ifndef XBYAK_DISABLE_AVX512>> %TARGET%
.\gen_avx512 | %SORT% >> %TARGET%
echo #ifdef XBYAK64>> %TARGET%
.\gen_avx512 64 | %SORT% >> %TARGET%
.\gen_ace_1 | %SORT% >> %TARGET%
echo #endif>> %TARGET%
echo #endif>> %TARGET%
exit /b 0

:ERR
echo update.bat failed
exit /b 1
