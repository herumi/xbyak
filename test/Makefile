TARGET = make_nm normalize_prefix
XBYAK_INC=../xbyak/xbyak.h

ifeq ($(MODE_BIT),64)
	XBYAK_OPT=-m64 -DXBYAK64
else
	XBYAK_OPT=-m32 -DXBYAK32
endif

all: $(TARGET)

CFLAGS_WARN=-Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal -Wpointer-arith

CFLAGS=-O2 -fomit-frame-pointer -Wall -fno-operator-names -I../ $(CFLAGS_WARN)
make_nm:
	$(CXX) $(CFLAGS) $(XBYAK_OPT) make_nm.cpp -o $@
normalize_prefix: normalize_prefix.cpp
	$(CXX) $(CFLAGS) $(XBYAK_OPT) normalize_prefix.cpp -o $@
test_mmx: test_mmx.cpp
	$(CXX) $(CFLAGS) $(XBYAK_OPT) test_mmx.cpp -o $@ -lpthread
jmp: jmp.cpp
	$(CXX) $(CFLAGS) -m32 -DXBYAK32 jmp.cpp -o $@

test: normalize_prefix jmp
	./test_nm.sh
	./test_nm.sh Y
	./test_nm.sh 64
	./test_nm.sh Y64
	./test_address.sh
	./test_address.sh 64
	./jmp

test_avx:
	./test_avx.sh
	./test_avx.sh Y
	./test_avx.sh 64
	./test_avx.sh Y64
clean:
	rm -rf *.o $(TARGET)

make_nm: make_nm.cpp $(XBYAK_INC)


