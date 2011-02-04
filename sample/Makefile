TARGET = test quantize bf toyvm test_util memfunc
XBYAK_INC=../xbyak/xbyak.h

BOOST_EXIT=$(shell echo "\#include <boost/spirit/core.hpp>" | (gcc -E - 2>/dev/null) | grep "boost/spirit/core.hpp" >/dev/null && echo "1")

BIT=32
ifeq ($(shell uname -m),x86_64)
BIT=64
endif
ifeq ($(shell uname -s),Darwin)
BIT=64
endif

ifeq ($(BIT),64)
TARGET += test64 bf64 memfunc64 test_util64
ifeq ($(BOOST_EXIT),1)
TARGET += calc64 calc2_64
endif
endif

ifeq ($(BOOST_EXIT),1)
TARGET += calc calc2
endif

all: $(TARGET)

CFLAGS_WARN=-Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal -Wpointer-arith

CFLAGS=-g -O2 -fomit-frame-pointer -Wall -fno-operator-names -I../ $(CFLAGS_WARN)

test:
	g++ $(CFLAGS) test0.cpp -o $@ -m32

quantize:
	g++ $(CFLAGS) quantize.cpp -o $@ -m32

calc:
	g++ $(CFLAGS) calc.cpp -o $@ -m32
calc64:
	g++ $(CFLAGS) calc.cpp -o $@ -m64
#calc2:
#	g++ $(CFLAGS) calc2.cpp -o $@ -m32
#calc2_64:
#	g++ $(CFLAGS) calc2.cpp -o $@ -m64

bf:
	g++ $(CFLAGS) bf.cpp -o $@ -m32
bf64:
	g++ $(CFLAGS) bf.cpp -o $@ -m64

memfunc:
	g++ $(CFLAGS) memfunc.cpp -o $@ -m32
memfunc64:
	g++ $(CFLAGS) memfunc.cpp -o $@ -m64

toyvm:
	g++ $(CFLAGS) toyvm.cpp -o $@ -m32

test64:
	g++ $(CFLAGS) test0.cpp -o $@ -m64
test_util:
	g++ $(CFLAGS) test_util.cpp -o $@ -m32
test_util64:
	g++ $(CFLAGS) test_util.cpp -o $@ -m64

clean:
	rm -rf *.o $(TARGET)

test : test0.cpp $(XBYAK_INC)
test64: test0.cpp $(XBYAK_INC)
quantize : quantize.cpp $(XBYAK_INC)
calc : calc.cpp $(XBYAK_INC)
calc64 : calc.cpp $(XBYAK_INC)
calc2 : calc2.cpp $(XBYAK_INC)
calc2_64 : calc2.cpp $(XBYAK_INC)
bf : bf.cpp $(XBYAK_INC)
bf64 : bf.cpp $(XBYAK_INC)
memfunc : memfunc.cpp $(XBYAK_INC)
memfunc64 : memfunc.cpp $(XBYAK_INC)
toyvm : toyvm.cpp $(XBYAK_INC)
test_util : test_util.cpp $(XBYAK_INC) ../xbyak/xbyak_util.h
test_util2 : test_util.cpp $(XBYAK_INC) ../xbyak/xbyak_util.h

