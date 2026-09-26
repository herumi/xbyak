#!/bin/sh

set -e

FILTER="grep -v warning"
CXX=${CXX:=g++}
CFLAGS_USER=${CFLAGS}
CFLAGS_WARN="$(cat CFLAGS_WARN.cfg)"

sub()
{
CFLAGS="$CFLAGS_USER $CFLAGS_WARN -I../ $OPT2"

echo $CXX $CFLAGS address.cpp -o address.exe
$CXX $CFLAGS address.cpp -o address.exe

./address.exe $1 > a.asm
echo "asm"
$EXE -f$OPT3 a.asm -l a.lst
awk '{printf "%s", sub(/-$/, "", $3) ? $3 : $3 ORS}' a.lst | $FILTER > ok.lst

echo "xbyak"
./address.exe $1 jit > nm.cpp
echo "compile nm_frame.cpp"
$CXX $CFLAGS -DXBYAK_TEST nm_frame.cpp -o nm_frame.exe
./nm_frame.exe > x.lst
diff -bB ok.lst x.lst && echo "ok"

}

if [ "$1" = "64" ]; then
	echo "nasm(64bit)"
	EXE=nasm
	OPT2=-DXBYAK64
	OPT3=win64

	sub 1
	sub 2
else
	echo "nasm(32bit)"
	EXE=nasm
	OPT2=-DXBYAK32
	OPT3=win32
	sub 1
fi

