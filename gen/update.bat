@echo off
set OPT=/EHsc -I../xbyak /W4 -D_CRT_SECURE_NO_WARNINGS
set TARGET=..\\xbyak\\xbyak_mnemonic.h
cl gen_code.cpp %OPT%
gen_code | sort > %TARGET%
echo #ifdef XBYAK_ENABLE_OMITTED_OPERAND>> %TARGET%
gen_code omit | sort >> %TARGET%
echo #endif>>%TARGET%
gen_code fixed >> %TARGET%
cl gen_avx512.cpp %OPT%
echo #ifndef XBYAK_DISABLE_AVX512>> %TARGET%
gen_avx512 |sort >> %TARGET%
echo #ifdef XBYAK64>> %TARGET%
gen_avx512 64 |sort >> %TARGET%
echo #endif>> %TARGET%
echo #endif>> %TARGET%
