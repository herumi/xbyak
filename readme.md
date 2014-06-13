
Xbyak 4.62 ; JIT assembler for x86(IA32), x64(AMD64, x86-64) by C++
=============

Abstract
-------------

This is a header file which enables dynamically to assemble x86(IA32), x64(AMD64, x86-64) mnemonic.

Feature
-------------
header file only
you can use Xbyak's functions at once if xbyak.h is included.

### Supported Instructions Sets

MMX/MMX2/SSE/SSE2/SSE3/SSSE3/SSE4/FPU(*partial*)/AVX/AVX2/FMA/VEX-encoded GPR

### Supported OS

* Windows Xp, Vista, Windows 7(32bit, 64bit)
* Linux(32bit, 64bit)
* Intel Mac ready

### Supported Compilers

* Visual Studio C++ VC2008 Pro, VC2010, VC2012
* gcc 4.7
* clang 3.3
* cygwin gcc 4.5.3
* icc 7.2

>Note: Xbyak uses and(), or(), xor(), not() functions, so "-fno-operator-names" option is required on gcc.
Or define XBYAK_NO_OP_NAMES and use and_(), or_(), xor_(), not_() instead of them.
and_(), or_(), xor_(), not_() are available if XBYAK_NO_OP_NAMES is not defined.

Install
-------------

The following files are necessary. Please add the path to your compile directories.

* xbyak.h
* xbyak_bin2hex.h
* xbyak_mnemonic.h

Linux:

    make install

These files are copied into /usr/local/include/xbyak

Break backward compatibility
-------------
* change the type of Xbyak::Error from enum to a class.
** get the enum value by cast to int.
* An (old) Reg32e class will split (new) Reg32e class and (new) RegExp.
(new) Reg32e class is Reg32 or Reg64.
(new) RegExp class is to deal with 'Reg32e + Reg32e * scale + disp'.
Please rename Reg32e as RegExp if you use (old) Reg32e as RegExp.

New Feature
-------------

AutoGrow mode is a mode that Xbyak grows memory automatically if necessary.
Call ready() before calling getCode() to calc address of jmp.

    struct Code : Xbyak::CodeGenerator {
      Code()
        : Xbyak::CodeGenerator(<default memory size>, Xbyak::AutoGrow)
      {
         ...
      }
    };
    Code c;
    c.ready(); // Don't forget to call this function

>Don't use the address returned by getCurr() before calling ready().
>It may be invalid address.
>RESTRICTION : rip addressing is not supported in AutoGrow

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

>dword, word and byte are member variables, then don't use dword as unsigned int, for example.

### AVX

You can omit a destination for almost 3-op mnemonics.

    vaddps(xmm1, xmm2, xmm3); // xmm1 <- xmm2 + xmm3
    vaddps(xmm2, xmm3); // xmm2 <- xmm2 + xmm3
    vaddps(xmm2, xmm3, ptr [rax]); // use ptr to access memory
    vgatherdpd(xmm1, ptr [ebp+123+xmm2*4], xmm3);

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
> you can use a label for immediate value of mov like as mov (eax, "L2");

#### 1. support @@, @f, @b like MASM

    L("@@"); // <A>
      jmp("@b"); // jmp to <A>
      jmp("@f"); // jmp to <B>
    L("@@"); // <B>
      jmp("@b"); // jmp to <B>
      mov(eax, "@b");
      jmp(eax); // jmp to <B>

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

### New Label class

L() and jxx() functions support a new Label class.

      Label label1, label2;
    L(label1);
      ...
      jmp(label1);
      ...
      jmp(label2);
      ...
    L(label2);

Moreover, assignL(dstLabel, srcLabel) method binds dstLabel with srcLabel.

      Label label1, label2;
    L(label1);
      ...
      jmp(label2);
      ...
      assignL(label2, label1); // label2 <= label1

The above jmp opecode jumps label1.

* Restriction:
* srcLabel must be used in L().
* dstLabel must not be used in L().

### Code size
The default max code size is 4096 bytes. Please set it in constructor of CodeGenerator() if you want to use large size.

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
* **XBYAK64_WIN** is defined on 64bit Windows(VC)
* **XBYAK64_GCC** is defined on 64bit gcc, cygwin

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
http://opensource.org/licenses/BSD-3-Clause

The files under test/cybozu/ are copied from cybozulib(https://github.com/herumi/cybozulib/),
which is licensed by BSD-3-Clause and are used for only tests.
The header files under xbyak/ are independent of cybozulib.

History
-------------
* 2014/Jun/13 ver 4.62 disable warning of VC2014
* 2014/May/30 ver 4.61 support bt, bts, btr, btc
* 2014/May/28 ver 4.60 support vcvtph2ps, vcvtps2ph
* 2014/Apr/11 ver 4.52 add detection of rdrand
* 2014/Mar/25 ver 4.51 remove state information of unreferenced labels
* 2014/Mar/16 ver 4.50 support new Label
* 2014/Mar/05 ver 4.40 fix wrong detection of BMI/enhanced rep on VirtualBox
* 2013/Dec/03 ver 4.30 support Reg::cvt8(), cvt16(), cvt32(), cvt64()
* 2013/Oct/16 ver 4.21 label support std::string
* 2013/Jul/30 ver 4.20 [break backward compatibility] split Reg32e class into RegExp(base+index*scale+disp) and Reg32e(means Reg32 or Reg64)
* 2013/Jul/04 ver 4.10 [break backward compatibility] change the type of Xbyak::Error from enum to a class
* 2013/Jun/21 ver 4.02 add putL(LABEL) function to put the address of the label
* 2013/Jun/21 ver 4.01 vpsllw, vpslld, vpsllq, vpsraw, vpsrad, vpsrlw, vpsrld, vpsrlq support (ymm, ymm, xmm).
                       support vpbroadcastb, vpbroadcastw, vpbroadcastd, vpbroadcastq(thanks to Gabest).
* 2013/May/30 ver 4.00 support AVX2, VEX-encoded GPR-instructions
* 2013/Mar/27 ver 3.80 support mov(reg, "label");
* 2013/Mar/13 ver 3.76 add cqo(), jcxz(), jecxz(), jrcxz()
* 2013/Jan/15 ver 3.75 add setSize() to modify generated code
* 2013/Jan/12 ver 3.74 add CodeGenerator::reset() ; add Allocator::useProtect()
* 2013/Jan/06 ver 3.73 use unordered_map if possible
* 2012/Dec/04 ver 3.72 eax, ebx, ... are member variables of CodeGenerator(revert), Xbyak::util::eax, ... are static const.
* 2012/Nov/17 ver 3.71 and_(), or_(), xor_(), not_() are available if XBYAK_NO_OP_NAMES is not defined.
* 2012/Nov/17 change eax, ebx, ptr and so on in CodeGenerator as static member and alias of them are defined in Xbyak::util.
* 2012/Nov/09 ver 3.70 XBYAK_NO_OP_NAMES macro is added to use and_() instead of and() (thanks to Mattias)
* 2012/Nov/01 ver 3.62 add fwait/fnwait/finit/fninit
* 2012/Nov/01 ver 3.61 add fldcw/fstcw
* 2012/May/03 ver 3.60 change interface of Allocator
* 2012/Mar/23 ver 3.51 fix userPtr mode
* 2012/Mar/19 ver 3.50 support AutoGrow mode
* 2011/Nov/09 ver 3.05 fix bit property of rip addresing / support movsxd
* 2011/Aug/15 ver 3.04 fix dealing with imm8 such as add(dword [ebp-8], 0xda); (thanks to lolcat)
* 2011/Jun/16 ver 3.03 fix __GNUC_PREREQ macro for Mac gcc(thanks to t_teruya)
* 2011/Apr/28 ver 3.02 do not use xgetbv on Mac gcc
* 2011/May/24 ver 3.01 fix typo of OSXSAVE
* 2011/May/23 ver 3.00 add vcmpeqps and so on
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
* 2008/Sep/18 support (ptr[rip + 32bit offset]) (thanks to Dango-Chu san)
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

