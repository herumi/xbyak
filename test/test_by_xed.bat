@echo off
setlocal
set XED=xed
set BIT=-64
set CFLAGS=-I ../ /EHsc /nologo
if "%1"=="-32" (
  set BIT=-32
  set CFLAGS=%CFLAGS% /DXBYAK32
  shift
)
if "%1"=="" (
  echo test_by_xed.bat [-32] ^<xbyak-cpp^>
  exit /b 1
)
copy %1 tmp.cpp
cl %CFLAGS% test_by_xed.cpp && test_by_xed.exe
%XED% %BIT% -set PREFETCHIT 1 -set PREFETCHRST 1 -set CLDEMOTE 1 -ir bin > out.txt
python3 test_by_xed.py %1 out.txt
