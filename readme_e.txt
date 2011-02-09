
    Xbyak 2.992 ; JIT assembler for x86(IA32), x64(AMD64, x86-64) by C++

-----------------------------------------------------------------------------
<Abstract>

This is a header file which enables dynamically to assemble x86(IA32),
x64(AMD64, x86-64) mnemonic.

-----------------------------------------------------------------------------
<Feature>
header file only
    you can use Xbyak's functions at once if xbyak.h is included.

MMX/MMX2/SSE/SSE2/SSE3/SSSE3/SSE4/FPU(partial)/AVX are available.

Windows Xp(32bit, 64bit), Vista, Linux(32bit, 64bit), Intel Mac ready
support Visual Studio C++ 2005 Express Ed., VC2008 Pro, VC2010,
mingw 3.4.2, icc 7.2, gcc 4.5, and so on.

Note: "-fno-operator-names" option is required on gcc to avoid analyzing
"and", "or", etc. as operators.

-----------------------------------------------------------------------------
<Install>
The following files are necessary. Please add the path to your compile
directories.

xbyak.h
xbyak_bin2hex.h
xbyak_mnemonic.h

Linux:
>make install
These files are copied into /usr/local/include/xbyak .
-----------------------------------------------------------------------------
<Syntax>

Make Xbyak::CodeGenerator and make the class method and get the function
pointer by calling cgetCode() and casting the return value.

NASM              Xbyak

mov eax, ebx  --> mov(eax, ebx);
inc ecx           inc(ecx);
ret           --> ret();

Addressing

(ptr|dword|word|byte) [base + index * (1|2|4|8) + displacement]
                      [rip + 32bit disp] ; x64 only

NASM                   Xbyak
mov eax, [ebx+ecx] --> mov (eax, ptr[ebx+ecx]);
test byte [esp], 4 --> test (byte [esp], 4);

NB. dword, word and byte are class members, then don't use dword as
unsigned int, for example.

AVX

You can omit a destination for almost 3-op mnemonics.

vaddps(xmm1, xmm2, xmm3); // xmm1 <- xmm2 + xmm3
vaddps(xmm2, xmm3); // xmm2 <- xmm2 + xmm3

Label

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

Call hasUndefinedLabel() to verify your code has no undefined label.

1. support @@, @f, @b like MASM

  L("@@"); // <A>
  jmp("@b"); // jmp to <A>
  jmp("@f"); // jmp to <B>
  L("@@"); // <B>
  jmp("@b"); // jmp to <B>

2. localization of label by calling inLocalLabel(), outLocallabel()

void func1()
{
    inLocalLabel();
    L(".lp"); // <A>
    ...
    jmp(".lp"); // jmpt to <A>
    outLocalLabel();
}

void func2()
{
    L(".lp"); // <B>
    func1();
    jmp(".lp"); // jmp to <B>
}

Code size
The default max code size is 2048 bytes. Please set it in constructor of
CodeGenerator() if you want to use large size.

class Quantize : public Xbyak::CodeGenerator {
public:
    Quantize()
        : CodeGenerator(8192)
    {
    }
    ...
};

See main.cpp

-----------------------------------------------------------------------------
<Macro>

XBYAK32 is defined on 32bit.
XBYAK64 is defined on 64bit.
XBYAK64_WIN is defined on 64bit Windows
XBYAK64_GCC is defined on 64bit gcc

-----------------------------------------------------------------------------
<Sample>

test0.cpp ; tiny sample of Xbyak(x86, x64)
quantize.cpp ; JIT optimized quantization by fast division(x86 only)
calc.cpp ; assemble and estimate a given polynomial(x86, x64)
bf.cpp ; JIT brainfuck(x86, x64)

-----------------------------------------------------------------------------
<Remark>

The current version does not support 3D Now!, 80bit FPU load/store
 and some special mnemonics.
Please mail to me if necessary.

-----------------------------------------------------------------------------
<License>

modified new BSD License
http://www.opensource.org/licenses/bsd-license.php
-----------------------------------------------------------------------------
<History>

2011/Feb/10 ver 2.992 beta fadd, fsubr, etc support st0 omitted parameter
2011/Feb/07 ver 2.991 beta fix pextrw reg, xmm, imm
2011/Feb/04 ver 2.99 beta support AVX
2010/Dec/08 ver 2.31 fix ptr [rip + 32bit offset], support rdtscp
2010/Oct/19 ver 2.30 support pclmulqdq, aesdec, aesdeclast, aesenc, aesenclast, aesimc, aeskeygenassist
2010/Jun/07 ver 2.29 fix call(<label>)
2010/Jun/17 ver 2.28 move some member functions to public
2010/Jun/01 ver 2.27 support encoding of mov(reg64, imm) like yasm(not nasm)
2010/May/24 ver 2.26 fix sub(rsp, 1000)
2010/Apr/26 ver 2.25 add jc/jnc(I forgot to implement them...)
2010/Apr/16 ver 2.24 change the prototype of rewrite() method
2010/Apr/15 ver 2.23 fix align() and xbyak_util.h for Mac
2010/Feb/16 ver 2.22 fix inLocalLabel()/outLocalLabel()
2009/Dec/09 ver 2.21 support cygwin(gcc 4.3.2)
2009/Nov/28 support a part of FPU
2009/Jun/25 fix mov(qword[rax], imm); (thanks to Martin)
2009/Mar/10 fix redundant REX.W prefix on jmp/call reg64
2009/Feb/24 add movq reg64, mmx/xmm; movq mmx/xmm, reg64
2009/Feb/13 movd(xmm7, dword[eax]) drops 0x66 prefix (thanks to Gabest)
2008/Dec/30 fix call in short relative address(thanks to kato san)
2008/Sep/18 support @@, @f, @b and localization of label(thanks to nobu-q san)
2008/Sep/18 support ptr [rip + 32bit offset] (thanks to Dango-Chu san)
2008/Jun/03 fix align(). mov(ptr[eax],1) throws ERR_MEM_SIZE_IS_NOT_SPECIFIED.
2008/Jun/02 support memory interface allocated by user
2008/May/26 fix protect() to avoid invalid setting(thanks to shinichiro_h san)
2008/Apr/30 add cmpxchg16b, cdqe
2008/Apr/29 support x64
2008/Apr/14 code refactoring
2008/Mar/12 add bsr/bsf
2008/Feb/14 fix output of sub eax, 1234 (thanks to Robert)
2007/Nov/5  support lock, xadd, xchg
2007/Nov/2  support SSSE3/SSE4 (thanks to Dango-Chu san)
2007/Feb/4  fix the bug that exception doesn't occur under the condition
            which the offset of jmp mnemonic without T_NEAR is over 127.
2007/Jan/21 fix the bug to create address like [disp]
            select smaller representation for mov (eax|ax|al, [disp])
2007/Jan/4  first version

-----------------------------------------------------------------------------
<Author>

MITSUNARI Shigeo(herumi at nifty dot com)

---
$Revision: 1.58 $
$Date: 2011/02/09 20:56:12 $
