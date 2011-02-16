
Xbyak 2.994 ; JIT assembler for x86(IA32), x64(AMD64, x86-64) by C++
=============

Abstract
-------------

This is a header file which enables dynamically to assemble x86(IA32), x64(AMD64, x86-64) mnemonic.

Feature
-------------
header file only
you can use Xbyak's functions at once if xbyak.h is included.

### Supported Instructions Sets

MMX/MMX2/SSE/SSE2/SSE3/SSSE3/SSE4/FPU(*partial*)/AVX

### Supported OS

* Windows Xp, Vista, Windows 7(32bit, 64bit)
* Linux(32bit, 64bit)
* Intel Mac ready

### Supported Compilers

* Visual Studio C++ 2005 Express Ed., VC2008 Pro, VC2010
* gcc 4.5
* mingw 3.4.2
* icc 7.2

>Note: "-fno-operator-names" option is required on gcc to avoid analyzing "and", "or", etc. as operators.

Install
-------------

The following files are necessary. Please add the path to your compile directories.

* xbyak.h
* xbyak_bin2hex.h
* xbyak_mnemonic.h

Linux:

    make install

These files are copied into /usr/local/include/xbyak

Syntax
-------------

Make Xbyak::CodeGenerator and make the class method and get the function
pointer by calling cgetCode() and casting the return value.

    NASM              Xbyak
    mov eax, ebx  --> mov(eax, ebx);
    inc ecx           inc(ecx);
    ret           --> ret();

### Addressing

    (ptr|dword|word|byte) [base + index * (1|2|4|8) + displacement]
                          [rip + 32bit disp] ; x64 only

    NASM                   Xbyak
    mov eax, [ebx+ecx] --> mov (eax, ptr[ebx+ecx]);
    test byte [esp], 4 --> test (byte [esp], 4);

>selector is not supported.

>you can use ptr for almost memory access unless you specify the size of memory.

>dword, word and byte are class members, then don't use dword as unsigned int, for example.

### AVX

You can omit a destination for almost 3-op mnemonics.

    vaddps(xmm1, xmm2, xmm3); // xmm1 <- xmm2 + xmm3
    vaddps(xmm2, xmm3); // xmm2 <- xmm2 + xmm3
    vaddps(xmm2, xmm3, ptr [rax]); // use ptr to access memory

### Label

    L("L1");
      jmp ("L1");

      jmp ("L2");
      ...
      a few mnemonics(8-bit displacement jmp)
      ...
    L("L2");

      jmp ("L3", T_NEAR);
      ...
      a lot of mnemonics(32-bit displacement jmp)
      ...
    L("L3");

>Call hasUndefinedLabel() to verify your code has no undefined label.

#### 1. support @@, @f, @b like MASM

    L("@@"); // <A>
      jmp("@b"); // jmp to <A>
      jmp("@f"); // jmp to <B>
    L("@@"); // <B>
      jmp("@b"); // jmp to <B>

#### 2. localization of label by calling inLocalLabel(), outLocallabel().

labels begining of period between inLocalLabel() and outLocalLabel()
are dealed with local label.
inLocalLabel() and outLocalLabel() can be nested.

    void func1()
    {
        inLocalLabel();
      L(".lp"); // <A> ; local label
        ...
        jmp(".lp"); // jmpt to <A>
      L("aaa"); // global label
        outLocalLabel();
    }

    void func2()
    {
        inLocalLabel();
      L(".lp"); // <B> ; local label
        func1();
        jmp(".lp"); // jmp to <B>
        inLocalLabel();
    }

### Code size
The default max code size is 2048 bytes. Please set it in constructor of CodeGenerator() if you want to use large size.

    class Quantize : public Xbyak::CodeGenerator {
    public:
      Quantize()
        : CodeGenerator(8192)
      {
      }
      ...
    };

### use user allocated memory

You can make jit code on prepaired memory.

    class Sample : public Xbyak::CodeGenerator {
    public:
        Sample(void *userPtr, size_t size)
            : Xbyak::CodeGenerator(size, userPtr)
        {
            ...
        }
    };

    const size_t codeSize = 1024;
    uint8 buf[codeSize + 16];

    // get 16-byte aligned address
    uint8 *p = Xbyak::CodeArray::getAlignedAddress(buf);

    // append executable attribute to the memory
    Xbyak::CodeArray::protect(p, codeSize, true);

    // construct your jit code on the memory
    Sample s(p, codeSize);

>See *sample/test0.cpp*

Macro
-------------

* **XBYAK32** is defined on 32bit.
* **XBYAK64** is defined on 64bit.
* **XBYAK64_WIN** is defined on 64bit Windows
* **XBYAK64_GCC** is defined on 64bit gcc

Sample
-------------

* test0.cpp ; tiny sample of Xbyak(x86, x64)
* quantize.cpp ; JIT optimized quantization by fast division(x86 only)
* calc.cpp ; assemble and estimate a given polynomial(x86, x64)
* bf.cpp ; JIT brainfuck(x86, x64)

Remark
-------------

The current version does not support 3D Now!, 80bit FPU load/store and some special mnemonics.
Please mail to me if necessary.

License
-------------

modified new BSD License
http://www.opensource.org/licenses/bsd-license.php

History
-------------

* 2011/Feb/16 ver 2.994 beta add vmovq for 32-bit mode(I forgot it)
* 2011/Feb/16 ver 2.993 beta remove cvtReg to avoid thread unsafe
* 2011/Feb/10 ver 2.992 beta support one argument syntax for fadd like nasm
* 2011/Feb/07 ver 2.991 beta fix pextrw reg, xmm, imm(Thanks to Gabest)
* 2011/Feb/04 ver 2.99 beta support AVX
* 2010/Dec/08 ver 2.31 fix ptr [rip + 32bit offset], support rdtscp
* 2010/Oct/19 ver 2.30 support pclmulqdq, aesdec, aesdeclast, aesenc, aesenclast, aesimc, aeskeygenassist
* 2010/Jun/07 ver 2.29 fix call(<label>)
* 2010/Jun/17 ver 2.28 move some member functions to public
* 2010/Jun/01 ver 2.27 support encoding of mov(reg64, imm) like yasm(not nasm)
* 2010/May/24 ver 2.26 fix sub(rsp, 1000)
* 2010/Apr/26 ver 2.25 add jc/jnc(I forgot to implement them...)
* 2010/Apr/16 ver 2.24 change the prototype of rewrite() method
* 2010/Apr/15 ver 2.23 fix align() and xbyak_util.h for Mac
* 2010/Feb/16 ver 2.22 fix inLocalLabel()/outLocalLabel()
* 2009/Dec/09 ver 2.21 support cygwin(gcc 4.3.2)
* 2009/Nov/28 support a part of FPU
* 2009/Jun/25 fix mov(qword[rax], imm); (thanks to Martin)
* 2009/Mar/10 fix redundant REX.W prefix on jmp/call reg64
* 2009/Feb/24 add movq reg64, mmx/xmm; movq mmx/xmm, reg64
* 2009/Feb/13 movd(xmm7, dword[eax]) drops 0x66 prefix (thanks to Gabest)
* 2008/Dec/30 fix call in short relative address(thanks to kato san)
* 2008/Sep/18 support @@, @f, @b and localization of label(thanks to nobu-q san)
* 2008/Sep/18 support ptr [rip + 32bit offset] (thanks to Dango-Chu san)
* 2008/Jun/03 fix align(). mov(ptr[eax],1) throws ERR_MEM_SIZE_IS_NOT_SPECIFIED.
* 2008/Jun/02 support memory interface allocated by user
* 2008/May/26 fix protect() to avoid invalid setting(thanks to shinichiro_h san)
* 2008/Apr/30 add cmpxchg16b, cdqe
* 2008/Apr/29 support x64
* 2008/Apr/14 code refactoring
* 2008/Mar/12 add bsr/bsf
* 2008/Feb/14 fix output of sub eax, 1234 (thanks to Robert)
* 2007/Nov/5  support lock, xadd, xchg
* 2007/Nov/2  support SSSE3/SSE4 (thanks to Dango-Chu san)
* 2007/Feb/4  fix the bug that exception doesn't occur under the condition which the offset of jmp mnemonic without T_NEAR is over 127.
* 2007/Jan/21 fix the bug to create address like [disp] select smaller representation for mov (eax|ax|al, [disp])
* 2007/Jan/4  first version

Author
-------------

MITSUNARI Shigeo(herumi at nifty dot com)

---
$Revision: 1.7 $
$Date: 2011/02/16 08:06:12 $
