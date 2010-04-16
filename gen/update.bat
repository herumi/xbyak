rem set STL_DIR=c:/s/STLport
rem set OPT=-GX -I%STL_DIR%/stlport /link /libpath:%STL_DIR%/lib
rem set OPT=-GX -I../xbyak
rem don't add /Ox
set OPT=/EHsc -I../xbyak
cl gen_code.cpp %OPT%
gen_code > ..\\xbyak\\xbyak_mnemonic.h
