TARGET = make_nm normalize_prefix
XBYAK_INC=../xbyak/xbyak.h

ifeq ($(MODE_BIT),64)
	XBYAK_OPT=-m64
	XBYAK_COPT=-DXBYAK64
else
	XBYAK_OPT=-m32
	XBYAK_COPT=-DXBYAK32
endif

all: $(TARGET)

CFLAGS_WARN=-Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal -Wpointer-arith

CFLAGS=-O2 -fomit-frame-pointer -Wall -fno-operator-names -I../ $(XBYAK_OPT) $(XBYAK_COPT) $(CFLAGS_WARN)
make_nm:
	g++ $(CFLAGS) make_nm.cpp -o $@
normalize_prefix: normalize_prefix.cpp
	g++ $(CFLAGS) normalize_prefix.cpp -o $@
test_mmx: test_mmx.cpp
	g++ $(CFLAGS) test_mmx.cpp -o $@ -lpthread

test: normalize_prefix
	./test_nm.sh
	./test_nm.sh Y
	./test_nm.sh 64
	./test_nm.sh Y64

clean:
	rm -rf *.o $(TARGET)

make_nm: make_nm.cpp $(XBYAK_INC)


