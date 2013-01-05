TARGET = make_nm normalize_prefix jmp address nm_frame
XBYAK_INC=../xbyak/xbyak.h
BIT=32
ifeq ($(shell uname -m),x86_64)
BIT=64
endif

ifeq ($(MODE_BIT),64)
	TARGET += jmp64 address64
else
endif

all: $(TARGET)

CFLAGS_WARN=-Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wfloat-equal -Wpointer-arith

CFLAGS=-O2 -fomit-frame-pointer -Wall -fno-operator-names -I../ $(CFLAGS_WARN) #-std=c++0x
make_nm:
	$(CXX) $(CFLAGS) make_nm.cpp -o $@
normalize_prefix: normalize_prefix.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) normalize_prefix.cpp -o $@
test_mmx: test_mmx.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) test_mmx.cpp -o $@ -lpthread
jmp: jmp.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) jmp.cpp -o $@ -m32
jmp64: jmp.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) jmp.cpp -o $@
address: address.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) address.cpp -o $@ -m32
address64: address.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) address.cpp -o $@
nm_frame: nm_frame.cpp ../xbyak/xbyak.h
	$(CXX) $(CFLAGS) nm_frame.cpp -o $@ -m32

test: normalize_prefix jmp
	./test_nm.sh
	./test_nm.sh Y
	./test_nm.sh 64
	./test_nm.sh Y64
	./test_address.sh
	./test_address.sh 64
	./jmp

test_avx: normalize_prefix
	./test_avx.sh
	./test_avx.sh Y
	./test_avx.sh 64
	./test_avx.sh Y64
clean:
	rm -rf *.o $(TARGET) lib_run

lib_run: lib_test.cpp lib_run.cpp lib.h
	$(CXX) $(CFLAGS) lib_run.cpp lib_test.cpp -o lib_run
make_nm: make_nm.cpp $(XBYAK_INC)


