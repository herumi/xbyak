#!/bin/sh

set -e
XED=${XED:=xed}
CXX=${CXX:=g++}
CFLAGS_USER=${CFLAGS}
CFLAGS_WARN="$(cat CFLAGS_WARN.cfg)"
PYTHON=${PYTHON:=python3}
echo $XED

BIT=-64
if [ "$1" = "-32" ]; then
  BIT=-32
  CFLAGS_USER="$CFLAGS_USER -DXBYAK32"
  shift
fi

XED_OPT=${XED_OPT:=$BIT -set PREFETCHIT 1 -set PREFETCHRST 1 -set CLDEMOTE 1}
#XED_OPT=${XED_OPT:=$BIT -chip-check FUTURE}

if [ $# -ne 1 ]; then
  echo "./test_by_xed.sh [-32] <xbyak-cpp>"
  exit 1
fi

TARGET=$1

CFLAGS="$CFLAGS_USER $CFLAGS_WARN -I ../"

echo "test:" $TARGET
cp $TARGET tmp.cpp
$CXX $CFLAGS test_by_xed.cpp -o test_by_xed.exe
./test_by_xed.exe || (echo "ERR test_by_xed"; exit 1)
echo "$XED ${XED_OPT} -ir bin > out.txt"
$XED ${XED_OPT} -ir bin > out.txt || (echo "ERR xed"; exit 1)
$PYTHON test_by_xed.py $TARGET out.txt || (echo "ERR test_by_xed.py"; exit 1)

