#include <stdio.h>
#include <string.h>
#include <string>
#include <xbyak/xbyak.h>
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

#if !defined(_WIN64) && !defined(__x86_64__)
	#define ONLY_32BIT
#endif

using namespace Xbyak;

void putNop(Xbyak::CodeGenerator *gen, int n)
{
	for (int i = 0; i < n; i++) {
		gen->nop();
	}
}
struct TestJmp : public Xbyak::CodeGenerator {
/*
     4                                  X0:
     5 00000004 EBFE                    jmp short X0
     6
     7                                  X1:
     8 00000006 <res 00000001>          dummyX1 resb 1
     9 00000007 EBFD                    jmp short X1
    10
    11                                  X126:
    12 00000009 <res 0000007E>          dummyX126 resb 126
    13 00000087 EB80                    jmp short X126
    14
    15                                  X127:
    16 00000089 <res 0000007F>          dummyX127 resb 127
    17 00000108 E97CFFFFFF              jmp near X127
    18
    19 0000010D EB00                    jmp short Y0
    20                                  Y0:
    21
    22 0000010F EB01                    jmp short Y1
    23 00000111 <res 00000001>          dummyY1 resb 1
    24                                  Y1:
    25
    26 00000112 EB7F                    jmp short Y127
    27 00000114 <res 0000007F>          dummyY127 resb 127
    28                                  Y127:
    29
    30 00000193 E980000000              jmp near Y128
    31 00000198 <res 00000080>          dummyY128 resb 128
    32                                  Y128:
*/
	TestJmp(int offset, bool isBack, bool isShort)
	{
		if (isBack) {
			L("@@");
			putNop(this, offset);
			jmp("@b");
		} else {
			if (isShort) {
				jmp("@f");
			} else {
				jmp("@f", T_NEAR);
			}
			putNop(this, offset);
			L("@@");
		}
	}
};

void test1()
{
	puts("test1");
	static const struct Tbl {
		int offset;
		bool isBack;
		bool isShort;
		uint8 result[6];
		int size;
	} tbl[] = {
		{ 0, true, true, { 0xeb, 0xfe }, 2 },
		{ 1, true, true, { 0xeb, 0xfd }, 2 },
		{ 126, true, true, { 0xeb, 0x80 }, 2 },
		{ 127, true, false, {0xe9, 0x7c, 0xff, 0xff, 0xff }, 5 },
		{ 0, false, true, { 0xeb, 0x00 }, 2 },
		{ 1, false, true, { 0xeb, 0x01 }, 2 },
		{ 127, false, true, { 0xeb, 0x7f }, 2 },
		{ 128, false, false, { 0xe9, 0x80, 0x00, 0x00, 0x00 }, 5 },
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		TestJmp jmp(p->offset, p->isBack, p->isShort);
		const uint8 *q = (const uint8*)jmp.getCode();
		if (p->isBack) q += p->offset; /* skip nop */
		for (int j = 0; j < p->size; j++) {
			if (q[j] != p->result[j]) {
				printf("err (%d,%d) %02x assume=%02x\n", (int)i, j, q[j], p->result[j]);
			}
		}
	}
}

struct TestJmp2 : public CodeGenerator {
/*
  1 00000000 90                      nop
  2 00000001 90                      nop
  3                                  f1:
  4 00000002 <res 0000007E>          dummyX1 resb 126
  6 00000080 EB80                     jmp f1
  7
  8                                  f2:
  9 00000082 <res 0000007F>          dummyX2 resb 127
 11 00000101 E97CFFFFFF               jmp f2
 12
 13
 14 00000106 EB7F                    jmp f3
 15 00000108 <res 0000007F>          dummyX3 resb 127
 17                                  f3:
 18
 19 00000187 E980000000              jmp f4
 20 0000018C <res 00000080>          dummyX4 resb 128
 22                                  f4:
*/
	explicit TestJmp2(void *p)
		: Xbyak::CodeGenerator(8192, p)
	{
		inLocalLabel();
		nop();
		nop();
	L(".f1");
		putNop(this, 126);
		jmp(".f1");
	L(".f2");
		putNop(this, 127);
		jmp(".f2", T_NEAR);

		jmp(".f3");
		putNop(this, 127);
	L(".f3");
		jmp(".f4", T_NEAR);
		putNop(this, 128);
	L(".f4");
		outLocalLabel();
	}
};

struct TestJmpCx : public CodeGenerator {
	explicit TestJmpCx(void *p)
		: Xbyak::CodeGenerator(16, p)
	{
		inLocalLabel();
	L(".lp");
#ifdef XBYAK64
		puts("TestJmpCx 64bit");
		/*
			67 E3 FD ; jecxz lp
			E3 FB    ; jrcxz lp
		*/
		jecxz(".lp");
		jrcxz(".lp");
#else
		puts("TestJmpCx 32bit");
		/*
			E3FE   ; jecxz lp
			67E3FB ; jcxz lp
		*/
		jecxz(".lp");
		jcxz(".lp");
#endif
		outLocalLabel();
	}
};

void testJmpCx()
{
	puts("testJmpCx");
	const struct {
		const char *p;
		size_t len;
	} tbl = {
#ifdef XBYAK64
		"\x67\xe3\xfd\xe3\xfb", 5
#else
		"\xe3\xfe\x67\xe3\xfb", 5
#endif
	};
	char buf[16] = {};
	TestJmpCx code(buf);
	if (memcmp(buf, tbl.p, tbl.len) == 0) {
	} else {
		puts("ng");
		for (int i = 0; i < 8; i++) {
			printf("%02x ", (unsigned char)buf[i]);
		}
		printf("\n");
	}
}

#ifdef _MSC_VER
	#pragma warning(disable : 4310)
#endif
void test2()
{
	puts("test2");
	std::string ok;
	ok.resize(0x18C + 128, (char)0x90);
	ok[0x080] = (char)0xeb;
	ok[0x081] = (char)0x80;

	ok[0x101] = (char)0xe9;
	ok[0x102] = (char)0x7c;
	ok[0x103] = (char)0xff;
	ok[0x104] = (char)0xff;
	ok[0x105] = (char)0xff;

	ok[0x106] = (char)0xeb;
	ok[0x107] = (char)0x7f;

	ok[0x187] = (char)0xe9;
	ok[0x188] = (char)0x80;
	ok[0x189] = (char)0x00;
	ok[0x18a] = (char)0x00;
	ok[0x18b] = (char)0x00;
	for (int j = 0; j < 2; j++) {
		TestJmp2 c(j == 0 ? 0 : Xbyak::AutoGrow);
		c.ready();
		std::string m((const char*)c.getCode(), c.getSize());
		if (m.size() != ok.size()) {
			printf("test2 err %d %d\n", (int)m.size(), (int)ok.size());
		} else {
			if (m != ok) {
				for (size_t i = 0; i < m.size(); i++) {
					if (m[i] != ok[i]) {
						printf("diff 0x%03x %02x %02x\n", (int)i, (unsigned char)m[i], (unsigned char)ok[i]);
					}
				}
			}
		}
	}
}

#ifdef ONLY_32BIT
int add5(int x) { return x + 5; }
int add2(int x) { return x + 2; }

struct Grow : Xbyak::CodeGenerator {
	Grow(int dummySize)
		: Xbyak::CodeGenerator(128, Xbyak::AutoGrow)
	{
		mov(eax, 100);
		push(eax);
		call((void*)add5);
		add(esp, 4);
		push(eax);
		call((void*)add2);
		add(esp, 4);
		ret();
		for (int i = 0; i < dummySize; i++) {
			db(0);
		}
	}
};

void test3()
{
	puts("test3");
	for (int dummySize = 0; dummySize < 40000; dummySize += 10000) {
		printf("dummySize=%d\n", dummySize);
		Grow g(dummySize);
		g.ready();
		int (*f)() = (int (*)())g.getCode();
		int x = f();
		const int ok = 107;
		if (x != ok) {
			printf("err %d assume %d\n", x, ok);
		}
	}
}
#endif

Xbyak::uint8 bufL[4096 * 32];
Xbyak::uint8 bufS[4096 * 2];

struct MyAllocator : Xbyak::Allocator {
	Xbyak::uint8 *alloc(size_t size)
	{
		if (size < sizeof(bufS)) {
			printf("test use bufS(%d)\n", (int)size);
			return bufS;
		}
		if (size < sizeof(bufL)) {
			printf("test use bufL(%d)\n", (int)size);
			return bufL;
		}
		fprintf(stderr, "no memory %d\n", (int)size);
		exit(1);
	}
	void free(Xbyak::uint8 *)
	{
	}
} myAlloc;

void dump(const std::string& m)
{
	printf("size=%d\n     ", (int)m.size());
	for (int i = 0; i < 16; i++) {
		printf("%02x ", i);
	}
	printf("\n     ");
	for (int i = 0; i < 16; i++) {
		printf("---");
	}
	printf("\n");
	for (size_t i = 0; i < m.size(); i++) {
		if ((i % 16) == 0) printf("%04x ", (int)(i / 16));
		printf("%02x ", (unsigned char)m[i]);
		if ((i % 16) == 15) putchar('\n');
	}
	putchar('\n');
}

void diff(const std::string& a, const std::string& b)
{
	if (a.size() != b.size()) printf("size diff %d %d\n", (int)a.size(), (int)b.size());
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			printf("diff %d(%04x) %02x %02x\n", (int)i, (int)i, (unsigned char)a[i], (unsigned char)b[i]);
		}
	}
}

struct Test4 : Xbyak::CodeGenerator {
	explicit Test4(int size, void *mode)
		: CodeGenerator(size, mode)
	{
		using namespace Xbyak;
		inLocalLabel();
		outLocalLabel();
		jmp(".x");
		for (int i = 0; i < 10; i++) {
			nop();
		}
	L(".x");
		ret();
	}
};
void test4()
{
	puts("test4");
	std::string fm, gm;
	Test4 fc(1024, 0);
	Test4 gc(5, Xbyak::AutoGrow);
	gc.ready();
	fm.assign((const char*)fc.getCode(), fc.getSize());
	gm.assign((const char*)gc.getCode(), gc.getSize());
//	dump(fm);
//	dump(gm);
	diff(gm, gm);
}

struct Test5 : Xbyak::CodeGenerator {
	explicit Test5(int size, int count, void *mode)
		: CodeGenerator(size, mode, &myAlloc)
	{
		using namespace Xbyak;
		inLocalLabel();
		mov(ecx, count);
		xor(eax, eax);
	L(".lp");
		for (int i = 0; i < count; i++) {
			L(Label::toStr(i));
			add(eax, 1);
			int to = 0;
			if (i < count / 2) {
				to = count - 1 - i;
			} else {
				to = count  - i;
			}
			if (i == count / 2) {
				jmp(".exit", T_NEAR);
			} else {
				jmp(Label::toStr(to), T_NEAR);
			}
		}
	L(".exit");
		sub(ecx, 1);
		jnz(".lp", T_NEAR);
		ret();
		outLocalLabel();
	}
};

void test5()
{
	puts("test5");
	std::string fm, gm;
	const int count = 50;
	int ret;
	Test5 fc(1024 * 64, count, 0);
	ret = ((int (*)())fc.getCode())();
	if (ret != count * count) {
		printf("err ret=%d, %d\n", ret, count * count);
	}
	fm.assign((const char*)fc.getCode(), fc.getSize());
	Test5 gc(10, count, Xbyak::AutoGrow);
	gc.ready();
#if 0
	ret = ((int (*)())gc.getCode())();
	if (ret != count * count) {
		printf("err ret=%d, %d\n", ret, count * count);
	} else {
		puts("ok");
	}
#endif
	gm.assign((const char*)gc.getCode(), gc.getSize());
	diff(fm, gm);
}

struct MovLabelCode : Xbyak::CodeGenerator {
	MovLabelCode(bool grow)
		: Xbyak::CodeGenerator(grow ? 128 : 4096, grow ? Xbyak::AutoGrow : 0)
	{
#ifdef XBYAK64
		const Reg64& a = rax;
#else
		const Reg32& a = eax;
#endif
		inLocalLabel();
		nop(); // 0x90
	L(".lp1");
		nop();
		mov(a, ".lp1"); // 0xb8 + <4byte> / 0x48bb + <8byte>
		nop();
		mov(a, ".lp2"); // 0xb8
		// force realloc if AutoGrow
		for (int i = 0; i < 256; i++) {
			nop();
		}
		nop();
	L(".lp2");
		outLocalLabel();
	}
};

size_t getValue(const uint8* p)
{
	size_t v = 0;
	for (size_t i = 0; i < sizeof(size_t); i++) {
		v |= p[i] << (i * 8);
	}
	return v;
}

void checkAddr(const uint8 *p, size_t offset, size_t expect)
{
	size_t v = getValue(p + offset);
	if (v == size_t(p) + expect) return;
	printf("err p=%p, offset=%lld, v=%llx(%llx), expect=%d\n", p, (long long)offset, (long long)v, (long long)(expect + size_t(p)), (int)expect);
}

void testMovLabel(bool grow)
{
	printf("testMovLabel grow=%d\n", grow);
	MovLabelCode code(grow);
	code.ready();
	const uint8* const p = code.getCode();
	const struct {
		int pos;
		uint8 ok;
	} tbl[] = {
#ifdef XBYAK32
		{ 0x00, 0x90 },
		// lp1:0x001
		{ 0x001, 0x90 },
		{ 0x002, 0xb8 },
		// 0x003
		{ 0x007, 0x90 },
		{ 0x008, 0xb8 },
		// 0x009
		{ 0x10d, 0x90 },
		// lp2:0x10e
#else
		{ 0x000, 0x90 },
		// lp1:0x001
		{ 0x001, 0x90 },
		{ 0x002, 0x48 },
		{ 0x003, 0xb8 },
		// 0x004
		{ 0x00c, 0x90 },
		{ 0x00d, 0x48 },
		{ 0x00e, 0xb8 },
		// 0x00f
		{ 0x117, 0x90 },
		// lp2:0x118
#endif
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		int pos = tbl[i].pos;
		uint8 x = p[pos];
		uint8 ok = tbl[i].ok;
		if (x != ok) {
			printf("err pos=%d, x=%02x, ok=%02x\n", pos, x, ok);
		}
	}
#ifdef XBYAK32
	checkAddr(p, 0x03, 0x001);
	checkAddr(p, 0x09, 0x10e);
#else
	checkAddr(p, 0x04, 0x001);
	checkAddr(p, 0x0f, 0x118);
#endif
}

struct MovLabel2Code : Xbyak::CodeGenerator {
	MovLabel2Code()
	{
#ifdef XBYAK64
		const Reg64& a = rax;
		const Reg64& c = rcx;
#else
		const Reg32& a = eax;
		const Reg32& c = ecx;
#endif
		xor(a, a);
		xor(c, c);
		jmp("in");
		ud2();
	L("@@"); // L1
		add(a, 2);
		mov(c, "@f");
		jmp(c); // goto L2
		ud2();
	L("in");
		mov(c, "@b");
		add(a, 1);
		jmp(c); // goto L1
		ud2();
	L("@@"); // L2
		add(a, 4);
		ret();
	}
};

void testMovLabel2()
{
	puts("tsetMovLabel2");
	MovLabel2Code code;
	int ret = code.getCode<int (*)()>()();
	if (ret != 7) printf("ERR=%d\n", ret);
}

struct TestLocal : public Xbyak::CodeGenerator {
	TestLocal(bool grow)
		: Xbyak::CodeGenerator(grow ? 128 : 4096, grow ? Xbyak::AutoGrow : 0)
	{
		xor_(eax, eax);
		inLocalLabel();
		jmp("start0", T_NEAR);
		L(".back");
		inc(eax); // 8
		jmp(".next", T_NEAR);
		L("start2");
		inc(eax); // 7
		jmp(".back", T_NEAR);
			inLocalLabel();
			L(".back");
			inc(eax); // 5
			putNop(this, 128);
			jmp(".next", T_NEAR);
			L("start1");
			inc(eax); // 4
			jmp(".back", T_NEAR);
				inLocalLabel();
				L(".back");
				inc(eax); // 2
				jmp(".next", T_NEAR);
				L("start0");
				inc(eax); // 1
				jmp(".back", T_NEAR);
				L(".next");
				inc(eax); // 3
				jmp("start1", T_NEAR);
				outLocalLabel();
			L(".next");
			inc(eax); // 6
			jmp("start2", T_NEAR);
			outLocalLabel();
		L(".next");
		inc(eax); // 9
		jmp("start3", T_NEAR);
			inLocalLabel();
			L(".back");
			inc(eax); // 14
			jmp("exit", T_NEAR);
		L("start4");
			inc(eax); // 13
			jmp(".back", T_NEAR);
			outLocalLabel();
		L("start3");
			inc(eax); // 10
			inLocalLabel();
			jmp(".next", T_NEAR);
			L(".back");
			inc(eax); // 12
			jmp("start4", T_NEAR);
			L(".next");
			inc(eax); // 11
			jmp(".back", T_NEAR);
			outLocalLabel();
		outLocalLabel();
		L("exit");
		inc(eax); // 15
		ret();
	}
};

void test6()
{
	for (int i = 0; i < 2; i++) {
		const bool grow = i == 1;
		printf("test6 grow=%d\n", i);
		TestLocal code(grow);
		if (grow) code.ready();
		int (*f)() = code.getCode<int (*)()>();
		int a = f();
		if (a != 15) {
			printf("ERR a=%d\n", a);
		}
	}
}

void testNewLabel()
{
	struct Code : Xbyak::CodeGenerator {
		Code(bool grow)
			: Xbyak::CodeGenerator(grow ? 128 : 4096, grow ? Xbyak::AutoGrow : 0)
		{
			xor_(eax, eax);
			{
				Label label1;
				Label label2;
				Label label3;
				Label label4;
				Label exit;
				jmp(label1, T_NEAR);
			L(label2);
				inc(eax); // 2
				jmp(label3, T_NEAR);
			L(label4);
				inc(eax); // 4
				jmp(exit, T_NEAR);
				putNop(this, 128);
			L(label3);
				inc(eax); // 3
				jmp(label4, T_NEAR);
			L(label1);
				inc(eax); // 1
				jmp(label2, T_NEAR);
			L(exit);
			}
			{
				Label label1;
				Label label2;
				Label label3;
				Label label4;
				Label exit;
				jmp(label1);
			L(label2);
				inc(eax); // 6
				jmp(label3);
			L(label4);
				inc(eax); // 8
				jmp(exit);
			L(label3);
				inc(eax); // 7
				jmp(label4);
			L(label1);
				inc(eax); // 5
				jmp(label2);
			L(exit);
			}
			ret();
		}
	};
	for (int i = 0; i < 2; i++) {
		const bool grow = i == 1;
		printf("testNewLabel grow=%d\n", grow);
		Code code(grow);
		if (grow) code.ready();
		int (*f)() = code.getCode<int (*)()>();
		int r = f();
		if (r != 8) {
			printf("err %d %d\n", i, r);
		}
	}
}

int main()
try {
#if 0
	test1();
	test2();
#ifdef ONLY_32BIT
	test3();
#endif
	test4();
	test5();
	test6();
	testJmpCx();
	testMovLabel(false);
	testMovLabel(true);
	testMovLabel2();
#endif
	testNewLabel();
} catch (std::exception& e) {
	printf("ERR:%s\n", e.what());
} catch (...) {
	printf("unknown error\n");
}
