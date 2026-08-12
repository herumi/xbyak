# To compile with -m32
# apt install g++-multilib
CXX_32 = $(CXX) -m32
CXX_64 = $(CXX) -m64
TARGET = make_nm.exe normalize_prefix.exe bad_address.exe misc.exe cvt_test.exe cvt_test32.exe noexception.exe misc32.exe detect_x32.exe avx10_test.exe
XBYAK_INC=../xbyak/xbyak.h ../xbyak/xbyak_mnemonic.h ../xbyak/xbyak_util.h
UNAME_S=$(shell uname -s)
ifeq ($(shell ./detect_x32.exe),x32)
X32?=1
endif
BIT=32
ifeq ($(shell uname -m),x86_64)
BIT=64
endif
ONLY_64BIT=0
ifeq ($(UNAME_S),Darwin)
  # 32-bit binary is not supported
  ONLY_64BIT=1
endif
ifeq ($(findstring MINGW64,$(UNAME_S)),MINGW64)
  ONLY_64BIT=1
endif
ifeq ($(ONLY_64BIT),0)
  TARGET += jmp.exe address.exe
endif

ifeq ($(BIT),64)
	TARGET += jmp64.exe address64.exe apx.exe mmap_allocator.exe
	TARGET += sf_test.exe cpumask_test.exe
endif

all: $(TARGET)

CFLAGS_WARN=$(shell cat CFLAGS_WARN.cfg)

CFLAGS=-O2 -Wall -I.. -I. $(CFLAGS_WARN) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) #-std=c++0x
make_nm.exe:
	$(CXX) $(CFLAGS) make_nm.cpp -o $@
normalize_prefix.exe: normalize_prefix.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) normalize_prefix.cpp -o $@
test_mmx: test_mmx.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) test_mmx.cpp -o $@ -lpthread
jmp.exe: jmp.cpp $(XBYAK_INC)
	$(CXX_32) $(CFLAGS) $< -o $@
jmp64.exe: jmp.cpp $(XBYAK_INC)
	$(CXX_64) $(CFLAGS) $< -o $@
address.exe: address.cpp $(XBYAK_INC)
	$(CXX_32) $(CFLAGS) $< -o $@
address64.exe: address.cpp $(XBYAK_INC)
	$(CXX_64) $(CFLAGS) $< -o $@
bad_address.exe: bad_address.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@
misc.exe: misc.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@
misc32.exe: misc.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@ -DXBYAK32
cvt_test.exe: cvt_test.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@
cvt_test32.exe: cvt_test.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@ -DXBYAK32
noexception.exe: noexception.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@ -fno-exceptions
apx.exe: apx.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@
mmap_allocator.exe: mmap_allocator.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@
avx10_test.exe: avx10_test.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@ -DXBYAK64
sf_test.exe: sf_test.cpp $(XBYAK_INC) sf_test_win.h sf_test_gcc.h
	$(CXX) $(CFLAGS) $< -o $@ #-DXBYAK64
cpumask_test.exe: cpumask_test.cpp $(XBYAK_INC)
	$(CXX) $(CFLAGS) $< -o $@

TEST_FILES=old.txt bf16.txt comp.txt misc.txt convert.txt minmax.txt saturation.txt apx.txt amx.txt
xed_test: detect_x32.exe
	@set -e; \
	for target in $(addprefix dataset/, $(TEST_FILES)); do \
		./test_by_xed.sh $$target || exit 1; \
	done

test_nm: normalize_prefix.exe $(TARGET)
	$(MAKE) -C ../gen
ifneq ($(ONLY_64BIT),1)
	CXX=$(CXX) ./test_nm.sh
	CXX=$(CXX) ./test_nm.sh noexcept
	CXX=$(CXX) ./test_nm.sh Y
	CXX=$(CXX) ./test_address.sh
	./jmp.exe
	./cvt_test32.exe
endif
	./bad_address.exe
	./misc.exe
	./misc32.exe
	./cvt_test.exe
	./noexception.exe
ifeq ($(BIT),64)
	CXX=$(CXX) ./test_address.sh 64
ifneq ($(X32),1)
	CXX=$(CXX) ./test_nm.sh 64
	CXX=$(CXX) ./test_nm.sh Y64
endif
	./jmp64.exe
	./apx.exe
	./avx10_test.exe
	./mmap_allocator.exe
endif

test_avx: normalize_prefix.exe
ifneq ($(ONLY_64BIT),0)
	CXX=$(CXX) ./test_avx.sh
	CXX=$(CXX) ./test_avx.sh Y
endif
ifeq ($(BIT),64)
	CXX=$(CXX) ./test_avx.sh 64
ifneq ($(X32),1)
	CXX=$(CXX) ./test_avx.sh Y64
endif
endif

test_avx512: normalize_prefix.exe
ifneq ($(ONLY_64BIT),0)
	CXX=$(CXX) ./test_avx512.sh
endif
ifeq ($(BIT),64)
	CXX=$(CXX) ./test_avx512.sh 64
endif

test_avx10: avx10_test.exe
	./avx10_test.exe

detect_x32.exe: detect_x32.c
	$(CC) $< -o $@

test: detect_x32.exe
	$(MAKE) test_nm
	$(MAKE) test_avx
	$(MAKE) test_avx512

test_all:
	$(MAKE) test
	$(MAKE) xed_test

update_sf_test: sf_test.cpp
	$(CXX) $(CFLAGS) sf_test.cpp -DXBYAK64_WIN -DDUMP -o sf_test_dump.exe && ./sf_test_dump.exe > sf_test_win.h
	$(CXX) $(CFLAGS) sf_test.cpp -DXBYAK64_GCC -DDUMP -o sf_test_dump.exe && ./sf_test_dump.exe > sf_test_gcc.h

clean:
	$(RM) a.asm *.lst *.obj *.o *.exe $(TARGET) nm.cpp

lib_run.exe: lib_test.cpp lib_run.cpp lib.h detect_x32.exe
	$(CXX) $(CFLAGS) lib_run.cpp lib_test.cpp -o lib_run.exe
make_nm.exe: make_nm.cpp make.h $(XBYAK_INC)

.PHONY: test
