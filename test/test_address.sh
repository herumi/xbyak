#!/bin/sh

FILTER=cat

sub()
{

CFLAGS="-Wall -fno-operator-names -I../ $OPT2"
echo "compile address.cpp"
g++ $CFLAGS address.cpp -o address

./address $1 > a.asm
echo "asm"
$EXE -f$OPT3 a.asm -l a.lst
awk '{print $3}' < a.lst > ok.lst

echo "xbyak"
./address $1 jit > nm.cpp
echo "compile nm_frame.cpp"
g++ $CFLAGS -DXBYAK_TEST nm_frame.cpp -o nm_frame
./nm_frame > x.lst
diff ok.lst x.lst && echo "ok"
wc x.lst

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

