#if defined(_MSC_VER) && (_MSC_VER <= 1200)
	#pragma warning(disable:4514)
	#pragma warning(disable:4786)
#endif
#include <stdio.h>
#include <stdlib.h>
#include "xbyak/xbyak.h"

class Sample : public Xbyak::CodeGenerator {
	void operator=(const Sample&);
public:
	Sample(void *ptr = 0, size_t size = Xbyak::DEFAULT_MAX_CODE_SIZE) : Xbyak::CodeGenerator(size, ptr) {}
	void gen()
	{
#ifdef XBYAK32
		mov(ecx, ptr [esp + 4]); // n
#elif defined(XBYAK64_GCC)
		mov(ecx, edi); // n
#endif
		xor(eax, eax); // sum
		test(ecx, ecx);
		jz(".exit");
		xor(edx, edx); // i
	L("@@");
		add(eax, edx);
		inc(edx);

		/*
			sample of local label
		*/
		inLocalLabel(); // from here
		jmp(".exit"); // jmp to not <B> but <A>
		nop();
		nop();
	L(".exit"); // <A> this label is different from <B>
		outLocalLabel(); // here

		cmp(edx, ecx);
		jbe("@b"); // jmp to previous @@
	L(".exit"); // <B>
		ret();
	}
};

class AddFunc : public Xbyak::CodeGenerator {
	void operator=(const AddFunc&);
public:
	AddFunc(int y)
	{
#ifdef XBYAK32
		mov(eax, ptr [esp + 4]);
		add(eax, y);
#elif defined(XBYAK64_WIN)
		lea(rax, ptr [rcx + y]);
#else
		lea(eax, ptr [edi + y]);
#endif
		ret();
	}
	int (*get() const)(int) { return (int (*)(int))getCode(); }
};

class CallAtoi : public Xbyak::CodeGenerator {
	void operator=(const CallAtoi&);
public:
	CallAtoi()
	{
		// rdi is pointer to string
#ifdef XBYAK64_WIN
#ifdef _DEBUG
		sub(rsp, 32); // return-address is destroied if 64bit debug mode
#endif
		mov(rax, (size_t)atoi);
		call(rax);
#ifdef _DEBUG
		add(rsp, 32);
#endif
#else
		call((void*)atoi);
#endif
		ret();
	}
	int (*get() const)(const char *) { return (int (*)(const char *))getCode(); }
};

class JmpAtoi : public Xbyak::CodeGenerator {
	void operator=(const JmpAtoi&);
public:
	JmpAtoi()
	{
		/* already pushed "456" */
#ifdef XBYAK64_WIN
		mov(rax, (size_t)atoi);
		jmp(rax);
#else
		jmp((void*)atoi);
#endif
	}
	int (*get() const)(const char *) { return (int (*)(const char *))getCode(); }
};

int main()
{
	try {
		Sample s;
		printf("Xbyak version=%s\n", s.getVersionString());
#ifdef XBYAK64_GCC
		puts("64bit mode(gcc)");
#elif defined(XBYAK64_WIN)
		puts("64bit mode(win)");
#else
		puts("32bit");
#endif
		s.gen();
		int (*func)(int) = (int (*)(int))s.getCode();
		for (int i = 0; i <= 10; i++) {
			printf("0 + ... + %d = %d\n", i, func(i));
		}
		for (int i = 0; i < 10; i++) {
			AddFunc a(i);
			int (*add)(int) = a.get();
			int y = add(i);
			printf("%d + %d = %d\n", i, i, y);
		}
		CallAtoi c;
		printf("call atoi(\"123\") = %d\n", c.get()("123"));
		JmpAtoi j;
		printf("jmp atoi(\"456\") = %d\n", j.get()("456"));
		{
			// use memory allocated by user
			using namespace Xbyak;
			const size_t codeSize = 1024;
			uint8 buf[codeSize + 16];
			uint8 *p = CodeArray::getAlignedAddress(buf);
			CodeArray::protect(p, codeSize, true);
			Sample s(p, codeSize);
			s.gen();
			int (*func)(int) = (int (*)(int))s.getCode();
			printf("0 + ... + %d = %d\n", 100, func(100));
			CodeArray::protect(p, codeSize, false);
		}
		puts("OK");
	} catch (Xbyak::Error err) {
		printf("ERR:%s(%d)\n", Xbyak::ConvertErrorToString(err), err);
	} catch (...) {
		printf("unknown error\n");
	}
	return 0;
}

