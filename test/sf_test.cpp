#define XBYAK_NO_OP_NAMES
#include <xbyak/xbyak_util.h>

#ifdef XBYAK32
	#error "this sample is for only 64-bit mode"
#endif

using namespace Xbyak::util;

struct Code : public Xbyak::CodeGenerator {
	void gen1()
	{
		StackFrame sf(this, 1);
		mov(rax, sf.p[0]);
	}
	void gen2()
	{
		StackFrame sf(this, 2);
		lea(rax, ptr [sf.p[0] + sf.p[1]]);
	}
	void gen3()
	{
		StackFrame sf(this, 3);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
	}
	void gen4()
	{
		StackFrame sf(this, 4);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		add(rax, sf.p[3]);
	}

	void gen5()
	{
		StackFrame sf(this, 4, UseRCX);
		xor_(rcx, rcx);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		add(rax, sf.p[3]);
	}

	void gen6()
	{
		StackFrame sf(this, 4, UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		add(rax, sf.p[3]);
	}

	void gen7()
	{
		StackFrame sf(this, 3, UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
	}

	void gen8()
	{
		StackFrame sf(this, 3, 3 | UseRCX | UseRDX);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(sf.t[0], 1);
		mov(sf.t[1], 2);
		mov(sf.t[2], 3);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
	}

	void gen9()
	{
		StackFrame sf(this, 3, 3 | UseRCX | UseRDX, 32);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		mov(sf.t[0], 1);
		mov(sf.t[1], 2);
		mov(sf.t[2], 3);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		mov(ptr [rsp + 8 * 0], rax);
		mov(ptr [rsp + 8 * 1], rax);
		mov(ptr [rsp + 8 * 2], rax);
		mov(ptr [rsp + 8 * 3], rax);
	}

	void gen10()
	{
		StackFrame sf(this, 4, 8 | UseRCX | UseRDX, 32);
		xor_(rcx, rcx);
		xor_(rdx, rdx);
		for (int i = 0; i < 8; i++) {
			mov(sf.t[i], i);
		}
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		add(rax, sf.p[3]);
		mov(ptr [rsp + 8 * 0], rax);
		mov(ptr [rsp + 8 * 1], rax);
		mov(ptr [rsp + 8 * 2], rax);
		mov(ptr [rsp + 8 * 3], rax);
	}

	void gen11()
	{
		StackFrame sf(this, 0, UseRCX);
		xor_(rcx, rcx);
		mov(rax, 3);
	}

	void gen12()
	{
		StackFrame sf(this, 4, UseRDX);
		xor_(rdx, rdx);
		mov(rax, sf.p[0]);
		add(rax, sf.p[1]);
		add(rax, sf.p[2]);
		add(rax, sf.p[3]);
	}
};

struct Code2 : Xbyak::CodeGenerator {
	Code2()
		: Xbyak::CodeGenerator(4096 * 32)
	{
	}
	void gen(int pNum, int tNum, int stackSizeByte)
	{
		StackFrame sf(this, pNum, tNum, stackSizeByte);
		if (tNum & UseRCX) xor_(rcx, rcx);
		if (tNum & UseRDX) xor_(rdx, rdx);
		for (int i = 0, n = tNum & ~(UseRCX | UseRDX); i < n; i++) {
			mov(sf.t[i], 5);
		}
		for (int i = 0; i < stackSizeByte; i++) {
			mov(byte [rsp + i], 0);
		}
		mov(rax, 1);
		for (int i = 0; i < pNum; i++) {
			add(rax, sf.p[i]);
		}
	}
};

static int errNum = 0;
void check(int x, int y)
{
	if (x != y) {
		printf("err x=%d, y=%d\n", x, y);
		errNum++;
	}
}

void verify(const Xbyak::uint8 *f, int pNum)
{
	switch (pNum) {
	case 0:
		check(1, Xbyak::CastTo<int (*)()>(f)());
		return;
	case 1:
		check(11, Xbyak::CastTo<int (*)(int)>(f)(10));
		return;
	case 2:
		check(111, Xbyak::CastTo<int (*)(int, int)>(f)(10, 100));
		return;
	case 3:
		check(1111, Xbyak::CastTo<int (*)(int, int, int)>(f)(10, 100, 1000));
		return;
	case 4:
		check(11111, Xbyak::CastTo<int (*)(int, int, int, int)>(f)(10, 100, 1000, 10000));
		return;
	default:
		printf("ERR pNum=%d\n", pNum);
		exit(1);
	}
}

void testAll()
{
	Code2 code;
	for (int stackSize = 0; stackSize < 32; stackSize += 7) {
		for (int pNum = 0; pNum < 4; pNum++) {
			for (int mode = 0; mode < 4; mode++) {
				int maxNum = 0;
				int opt = 0;
				if (mode == 0) {
					maxNum = 10;
				} else if (mode == 1) {
					maxNum = 9;
					opt = UseRCX;
				} else if (mode == 2) {
					maxNum = 9;
					opt = UseRDX;
				} else {
					maxNum = 8;
					opt = UseRCX | UseRDX;
				}
				for (int tNum = 0; tNum < maxNum; tNum++) {
//					printf("pNum=%d, tNum=%d, stackSize=%d\n", pNum, tNum | opt, stackSize);
					const Xbyak::uint8 *f = code.getCurr();
					code.gen(pNum, tNum | opt, stackSize);
					verify(f, pNum);
				}
			}
		}
	}
}

void testPartial()
{
	Code code;
	int (*f1)(int) = code.getCurr<int (*)(int)>();
	code.gen1();
	check(5, f1(5));

	int (*f2)(int, int) = code.getCurr<int (*)(int, int)>();
	code.gen2();
	check(9, f2(3, 6));

	int (*f3)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen3();
	check(14, f3(1, 4, 9));

	int (*f4)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen4();
	check(30, f4(1, 4, 9, 16));

	int (*f5)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen5();
	check(23, f5(2, 5, 7, 9));

	int (*f6)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen6();
	check(18, f6(3, 4, 5, 6));

	int (*f7)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen7();
	check(12, f7(3, 4, 5));

	int (*f8)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen8();
	check(23, f8(5, 8, 10));

	int (*f9)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen9();
	check(60, f9(10, 20, 30));

	int (*f10)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen10();
	check(100, f10(10, 20, 30, 40));

	int (*f11)() = code.getCurr<int (*)()>();
	code.gen11();
	check(3, f11());

	int (*f12)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen12();
	check(24, f12(3, 5, 7, 9));
}

void put(const Xbyak::util::Pack& p)
{
	for (size_t i = 0, n = p.size(); i < n; i++) {
		printf("%s ", p[i].toString());
	}
	printf("\n");
}

void verifyPack(const Xbyak::util::Pack& p, const int *tbl, size_t tblNum)
{
	for (size_t i = 0; i < tblNum; i++) {
		check(p[i].getIdx(), tbl[i]);
	}
}

void testPack()
{
	const int N = 10;
	Xbyak::Reg64 regTbl[N];
	for (int i = 0; i < N; i++) {
		regTbl[i] = Xbyak::Reg64(i);
	}
	Xbyak::util::Pack p(regTbl, N);
	const struct {
		int pos;
		int num;
		int tbl[10];
	} tbl[] = {
		{ 0, 10, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } },
		{ 1, 9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } },
		{ 2, 8, { 2, 3, 4, 5, 6, 7, 8, 9 } },
		{ 3, 7, { 3, 4, 5, 6, 7, 8, 9 } },
		{ 4, 6, { 4, 5, 6, 7, 8, 9 } },
		{ 5, 5, { 5, 6, 7, 8, 9 } },
		{ 6, 4, { 6, 7, 8, 9 } },
		{ 7, 3, { 7, 8, 9 } },
		{ 8, 2, { 8, 9 } },
		{ 9, 1, { 9 } },
		{ 3, 5, { 3, 4, 5, 6, 7 } },
	};
	for (size_t i = 0; i < sizeof(tbl) / sizeof(*tbl); i++) {
		const int pos = tbl[i].pos;
		const int num = tbl[i].num;
		verifyPack(p.sub(pos, num), tbl[i].tbl, num);
		if (pos + num == N) {
			verifyPack(p.sub(pos), tbl[i].tbl, num);
		}
	}
}

int main()
	try
{
	testAll();

	testPartial();
	testPack();
	printf("errNum=%d\n", errNum);
} catch (std::exception& e) {
	printf("err %s\n", e.what());
	return 1;
} catch (...) {
	puts("ERR");
	return 1;
}

