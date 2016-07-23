set OPT=/EHsc -I../xbyak /W4 -D_CRT_SECURE_NO_WARNINGS
cl gen_code.cpp %OPT%
gen_code > ..\\xbyak\\xbyak_mnemonic.h
cl gen_avx512.cpp %OPT%
gen_avx512 >> ..\\xbyak\\xbyak_mnemonic.h
