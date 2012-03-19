@echo off
echo ** nasm-avx(32bit) ***
call test_avx
echo ** nasm-avx(64bit) ***
call test_avx 64
echo ** yasm-avx(32bit) ***
call test_avx Y
echo ** yasm-avx(64bit) ***
call test_avx Y64
