#!/bin/sh

set -e

FILTER="grep -v warning"
CXX=${CXX:=g++}
CFLAGS_USER=${CFLAGS}
CFLAGS_WARN="$(cat CFLAGS_WARN.cfg)"

case $1 in
64)
	echo "nasm(64bit)"
	EXE=nasm
	OPT2=-DXBYAK64
	OPT3=win64
	FILTER=./normalize_prefix.exe
	;;
*)
	echo "nasm(32bit)"
	EXE=nasm
	OPT2=-DXBYAK32
	OPT3=win32
	;;
esac

CFLAGS="$CFLAGS_USER $CFLAGS_WARN -I../ $OPT2 -DUSE_AVX512"
echo "compile make_512.cpp"
$CXX $CFLAGS make_512.cpp -o make_512.exe

./make_512.exe > a.asm
echo "asm"
$EXE -f$OPT3 a.asm -l a.lst
awk '{printf "%s", sub(/-$/, "", $3) ? $3 : $3 ORS}' a.lst | $FILTER > ok.lst

echo "xbyak"
./make_512.exe jit > nm.cpp
echo "compile nm_frame.cpp"
$CXX $CFLAGS -DXBYAK_TEST nm_frame.cpp -o nm_frame.exe -DXBYAK_AVX512
./nm_frame.exe | $FILTER > x.lst
diff -bB ok.lst x.lst && echo "ok"
