#include <xbyak/xbyak_util.h>
#include <cinttypes>
#include <cstring>
#include <vector>
#include <map>

#ifdef XBYAK32
	#error "this sample is for only 64-bit mode"
#endif

using namespace Xbyak::util;

#ifndef DUMP
#ifdef _MSC_VER
	#pragma warning(disable : 4459)
	#pragma warning(disable : 4996)
#endif
#include <cybozu/test.hpp>

#ifdef XBYAK64_WIN
#include "sf_test_win.h"
#endif
#ifdef XBYAK64_GCC
#include "sf_test_gcc.h"
#endif

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

	/*
		int64_t f(const int64_t a[13]) { return sum-of-a[]; }
	*/
	void gen13()
	{
		StackFrame sf(this, 1, 13);
		for (int i = 0; i < 13; i++) {
			mov(sf.t[i], ptr[sf.p[0] + i * 8]);
		}
		mov(rax, sf.t[0]);
		for (int i = 1; i < 13; i++) {
			add(rax, sf.t[i]);
		}
	}
	/*
		same as gen13
	*/
	void gen14()
	{
		StackFrame sf(this, 1, 11 | UseRCX | UseRDX);
		Pack t = sf.t;
		t.append(rcx);
		t.append(rdx);
		for (int i = 0; i < 13; i++) {
			mov(t[i], ptr[sf.p[0] + i * 8]);
		}
		mov(rax, t[0]);
		for (int i = 1; i < 13; i++) {
			add(rax, t[i]);
		}
	}
	/*
		return (1 << 15) - 1;
	*/
	void gen15()
	{
		StackFrame sf(this, 0, 14, 8);
		Pack t = sf.t;
		t.append(rax);
		for (int i = 0; i < 15; i++) {
			mov(t[i], uint64_t(1) << i);
		}
		mov(qword[rsp], 0);
		for (int i = 0; i < 15; i++) {
			add(ptr[rsp], t[i]);
		}
		mov(rax, ptr[rsp]);
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
	void gen2(int pNum, int tNum, int stackSizeByte)
	{
		StackFrame sf(this, pNum, tNum, stackSizeByte);
		mov(rax, rsp);
	}
};


void verify(const uint8_t *_f, int pNum)
{
	uint8_t *f = const_cast<uint8_t*>(_f);
	switch (pNum) {
	case 0:
		CYBOZU_TEST_EQUAL(1, reinterpret_cast<int (*)()>(f)());
		return;
	case 1:
		CYBOZU_TEST_EQUAL(11, reinterpret_cast<int (*)(int)>(f)(10));
		return;
	case 2:
		CYBOZU_TEST_EQUAL(111, reinterpret_cast<int (*)(int, int)>(f)(10, 100));
		return;
	case 3:
		CYBOZU_TEST_EQUAL(1111, reinterpret_cast<int (*)(int, int, int)>(f)(10, 100, 1000));
		return;
	case 4:
		CYBOZU_TEST_EQUAL(11111, reinterpret_cast<int (*)(int, int, int, int)>(f)(10, 100, 1000, 10000));
		return;
	default:
		printf("ERR pNum=%d\n", pNum);
		exit(1);
	}
}

CYBOZU_TEST_AUTO(param)
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
					const uint8_t *f = code.getCurr();
					code.gen(pNum, tNum | opt, stackSize);
					verify(f, pNum);
					/*
						check rsp is 16-byte aligned if stackSize > 0
					*/
					if (stackSize > 0) {
						Code2 c2;
						c2.gen2(pNum, tNum | opt, stackSize);
						uint64_t addr = c2.getCode<uint64_t (*)()>()();
						CYBOZU_TEST_EQUAL(addr % 16, 0);
					}
				}
			}
		}
	}
}

CYBOZU_TEST_AUTO(args)
{
	Code code;
	int (*f1)(int) = code.getCurr<int (*)(int)>();
	code.gen1();
	CYBOZU_TEST_EQUAL(5, f1(5));

	int (*f2)(int, int) = code.getCurr<int (*)(int, int)>();
	code.gen2();
	CYBOZU_TEST_EQUAL(9, f2(3, 6));

	int (*f3)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen3();
	CYBOZU_TEST_EQUAL(14, f3(1, 4, 9));

	int (*f4)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen4();
	CYBOZU_TEST_EQUAL(30, f4(1, 4, 9, 16));

	int (*f5)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen5();
	CYBOZU_TEST_EQUAL(23, f5(2, 5, 7, 9));

	int (*f6)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen6();
	CYBOZU_TEST_EQUAL(18, f6(3, 4, 5, 6));

	int (*f7)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen7();
	CYBOZU_TEST_EQUAL(12, f7(3, 4, 5));

	int (*f8)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen8();
	CYBOZU_TEST_EQUAL(23, f8(5, 8, 10));

	int (*f9)(int, int, int) = code.getCurr<int (*)(int, int, int)>();
	code.gen9();
	CYBOZU_TEST_EQUAL(60, f9(10, 20, 30));

	int (*f10)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen10();
	CYBOZU_TEST_EQUAL(100, f10(10, 20, 30, 40));

	int (*f11)() = code.getCurr<int (*)()>();
	code.gen11();
	CYBOZU_TEST_EQUAL(3, f11());

	int (*f12)(int, int, int, int) = code.getCurr<int (*)(int, int, int, int)>();
	code.gen12();
	CYBOZU_TEST_EQUAL(24, f12(3, 5, 7, 9));

	{
		int64_t tbl[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
		int64_t (*f13)(const int64_t*) = code.getCurr<int64_t (*)(const int64_t*)>();
		code.gen13();
		CYBOZU_TEST_EQUAL(91, f13(tbl));

		int64_t (*f14)(const int64_t*) = code.getCurr<int64_t (*)(const int64_t*)>();
		code.gen14();
		CYBOZU_TEST_EQUAL(91, f14(tbl));
	}
	int (*f15)() = code.getCurr<int (*)()>();
	code.gen15();
	CYBOZU_TEST_EQUAL((1 << 15) - 1, f15());
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
		CYBOZU_TEST_EQUAL(p[i].getIdx(), tbl[i]);
	}
}

CYBOZU_TEST_AUTO(pack)
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

struct CloseCode : Xbyak::CodeGenerator {
	CloseCode(size_t mode)
	{
		switch (mode) {
		case 0:
			{
				StackFrame sf(this, 0);
				// close() is automatically called.
			}
			break;

		case 1:
			{
				StackFrame sf(this, 0, 0, 0, false);
				sf.close(); // Explicitly call close().
				setProtectModeRE(); // Ensure that no writes occur in destructor by setting read-exec
			}
			break;

		case 2:
			{
				StackFrame sf(this, 0, 0, 0, false);
				sf.close(); // Explicitly call close().
				sf.close(); // Explicitly call close().
				setProtectModeRE(); // Ensure that no writes occur in destructor by setting read-exec
			}
			break;
		default:
			CYBOZU_TEST_ASSERT(false);
		}
	}
};

CYBOZU_TEST_AUTO(close)
{
	const size_t expectedTbl[] = {
		1, 1, 2,
	};
	for (size_t i = 0; i < sizeof(expectedTbl)/sizeof(expectedTbl[0]); i++) {
		CloseCode c(i);
		CYBOZU_TEST_EQUAL(c.getSize(), expectedTbl[i]);
	}
}
#endif

struct ParamId {
	int pNum;
	int tNum;
	int useRegs;
	int stackSizeByte;
	struct encoded {
		uint8_t pNum;
		uint8_t tNum;
		uint16_t useRegsLow;
		uint16_t useRegsHigh;
		uint8_t stackSizeByte;
		uint8_t reserved;
	};
	uint64_t id() const
	{
		encoded e;
		uint32_t ur = uint32_t(useRegs) >> 5;
		e.pNum = uint8_t(pNum);
		e.tNum = uint8_t(tNum);
		e.useRegsLow = uint16_t(ur);
		e.useRegsHigh = uint16_t(ur >> 16);
		e.stackSizeByte = uint8_t(stackSizeByte);
		e.reserved = 0;
		uint64_t v;
		memcpy(&v, &e, sizeof(v));
		return v;
	};
	void set_id(uint64_t v)
	{
		encoded e;
		memcpy(&e, &v, sizeof(e));
		pNum = e.pNum;
		tNum = e.tNum;
		useRegs = int(uint32_t(e.useRegsLow) | (uint32_t(e.useRegsHigh) << 16)) << 5;
		stackSizeByte = e.stackSizeByte;
	}
};

typedef std::vector<uint8_t> Bytes;

#ifndef DUMP
void cmpAndDumpIfFailed(int rhs, int lhs, const Bytes& d)
{
	CYBOZU_TEST_EQUAL(rhs, lhs);
	if (rhs != lhs) {
		FILE *fp = fopen("dump.bin", "wb");
		fwrite(d.data(), 1, d.size(), fp);
		fclose(fp);
		exit(1);
	}
}
#endif

void stackFrameTest()
{
	struct Data {
		ParamId paramId;
		Bytes code;
	};
	typedef std::map<uint64_t, Data> DataMap;
	DataMap dataMap;

	struct Code : Xbyak::CodeGenerator {
		Code(int pNum, int tNum, int useRegs, int stackSizeByte)
		{
			StackFrame sf(this, pNum, tNum|useRegs, stackSizeByte);
			// modify
			for (int i = 0; i < tNum; i++) {
				mov(sf.t[i], 12345);
			}
			if (useRegs & UseRCX) {
				mov(rcx, 12345);
			}
			if (useRegs & UseRDX) {
				mov(rdx, 12345);
			}
			if (useRegs & UseRSI) {
				mov(rsi, 1000);
			}
			if (useRegs & UseRDI) {
				mov(rdi, 2000);
			}
			// use rbp if UseRBP and !UseRBPAsFramePointer
			if ((useRegs & UseRBPAsFramePointer) == UseRBP) {
				mov(rbp, 3000);
			}
			// eax is sum of all params and (esp & 15) if stackSizeByte > 0
			if (stackSizeByte > 0) {
				mov(eax, esp);
				and_(eax, 15);
			} else {
				xor_(eax, eax);
			}
			for (int i = 0; i < pNum; i++) {
				add(rax, sf.p[i]);
			}
		}
	};
	static const uint8_t stackSizeTbl[] = { 0, 33 };
	for (int pNum = 0; pNum <= 4; pNum++) {
		for (int tNum = 0; tNum <= 14; tNum++) {
			// skip middle middle values of tNum to keep the headers small
			if (3 < tNum && tNum < 13) continue;
			for (int i = 0; i < (1<<6); i++) {
				int totalNum = pNum + tNum;
				int useRegs = 0;
				if (i & 1) { useRegs |= UseRCX; totalNum++; }
				if (i & 2) { useRegs |= UseRDX; totalNum++; }
				if (i & 4) { useRegs |= UseRSI; totalNum++; }
				if (i & 8) { useRegs |= UseRDI; totalNum++; }
				// UseRBP and UseRBPAsFramePointer are mutually exclusive
				if (i & 16) { useRegs |= UseRBP; totalNum++; }
				if (!(i & 16) && (i & 32)) { useRegs |= UseRBPAsFramePointer; totalNum++; }
				if (totalNum > 14) continue;
				for (size_t j = 0; j < sizeof(stackSizeTbl)/sizeof(stackSizeTbl[0]); j++) {
					int stackSizeByte = stackSizeTbl[j];
//fprintf(stderr, "pNum=%d, tNum=%d, useRegs=0x%X stackSizeByte=%d\n", pNum, tNum, useRegs, stackSizeByte);
					Code c(pNum, tNum, useRegs, stackSizeByte);
//fprintf(stderr, "code size = %d\n", int(c.getSize()));
					Data d;
					d.paramId.pNum = pNum;
					d.paramId.tNum = tNum;
					d.paramId.useRegs = useRegs;
					d.paramId.stackSizeByte = stackSizeByte;
					d.code.assign(c.getCode(), c.getCode() + c.getSize());
					dataMap[d.paramId.id()] = d;
#ifndef DUMP
					switch (pNum) {
					case 0:
						{
							int (*f)() = c.getCode<int (*)()>();
							CYBOZU_TEST_EQUAL(0, f());
//							cmpAndDumpIfFailed(0, f(), d.code);
							break;
						}
					case 1:
						{
							int (*f1)(int) = c.getCode<int (*)(int)>();
							CYBOZU_TEST_EQUAL(1, f1(1));
							break;
						}
					case 2:
						{
							int (*f2)(int, int) = c.getCode<int (*)(int, int)>();
							CYBOZU_TEST_EQUAL(11, f2(1, 10));
							break;
						}
					case 3:
						{
							int (*f3)(int, int, int) = c.getCode<int (*)(int, int, int)>();
							CYBOZU_TEST_EQUAL(111, f3(1, 10, 100));
							break;
						}
					case 4:
						{
							int (*f4)(int, int, int, int) = c.getCode<int (*)(int, int, int, int)>();
							CYBOZU_TEST_EQUAL(1111, f4(1, 10, 100, 1000));
							break;
						}
					}
#endif
				}
			}
		}
	}
#ifdef DUMP
		for (DataMap::const_iterator it = dataMap.begin(); it != dataMap.end(); ++it) {
			const Data& d = it->second;
			printf("static const uint8_t code_%" PRIx64 "[] = {\n", d.paramId.id());
			for (size_t j = 0; j < d.code.size(); j++) {
				if (j % 16 == 0) {
					if (j > 0) printf("\n");
					printf("\t");
				}
				if (j > 0) printf(" ");
				printf("0x%02x,", d.code[j]);
			}
			printf("\n};\n");
		}
		printf("static const struct {\n");
		printf("\tuint64_t paramId;\n");
		printf("\tconst uint8_t *code;\n");
		printf("\tsize_t codeSize;\n");
		printf("} g_dataVec[] = {\n");
		for (DataMap::const_iterator it = dataMap.begin(); it != dataMap.end(); ++it) {
			const Data& d = it->second;
			printf("\t{ 0x%" PRIx64 ", code_%" PRIx64 ", %zu },\n", d.paramId.id(), d.paramId.id(), d.code.size());
		}
		printf("};\n");
#else
		DataMap dataMapExpected;
		for (size_t i = 0; i < sizeof(g_dataVec) / sizeof(*g_dataVec); i++) {
			const uint64_t id = g_dataVec[i].paramId;
			Data d;
			d.paramId.set_id(id);
			d.code.assign(g_dataVec[i].code, g_dataVec[i].code + g_dataVec[i].codeSize);
			dataMapExpected[id] = d;
		}
		CYBOZU_TEST_EQUAL(dataMap.size(), dataMapExpected.size());
		for (DataMap::const_iterator it = dataMapExpected.begin(); it != dataMapExpected.end(); ++it) {
			const uint64_t id = it->first;
			DataMap::const_iterator it2 = dataMap.find(id);
			CYBOZU_TEST_ASSERT(it2 != dataMap.end());
			const Data& d = it2->second;
			const Data& dExpected = it->second;
			CYBOZU_TEST_EQUAL(d.code.size(), dExpected.code.size());
			CYBOZU_TEST_EQUAL_ARRAY(d.code.data(), dExpected.code.data(), d.code.size());
		}
#endif
}

/*
	Test StackFrame APX flag combinations.
	Covers UsePUSH2, UsePPX, UsePUSH2|UsePPX, UseR30R31 and combinations.
	A small parameter/register subset keeps the golden file manageable.
*/
void apxStackFrameTest()
{
	struct Data {
		ParamId paramId;
		Bytes code;
	};
	typedef std::map<uint64_t, Data> DataMap;
	DataMap dataMap;

	struct Code : Xbyak::CodeGenerator {
		Code(int pNum, int tNum, int useRegs, int stackSizeByte)
		{
			StackFrame sf(this, pNum, tNum|useRegs, stackSizeByte);
			for (int i = 0; i < tNum; i++) {
				mov(sf.t[i], 12345);
			}
			if (useRegs & UseRCX) mov(rcx, 12345);
			if (useRegs & UseRDX) mov(rdx, 12345);
			if (useRegs & UseRSI) mov(rsi, 1000);
			if (useRegs & UseRDI) mov(rdi, 2000);
			if ((useRegs & UseRBPAsFramePointer) == UseRBP) mov(rbp, 3000);
			if (useRegs & UseR30R31) {
				mov(r30, 4321);
				mov(r31, 8765);
			}
			if (stackSizeByte > 0) {
				mov(eax, esp);
				and_(eax, 15);
			} else {
				xor_(eax, eax);
			}
			for (int i = 0; i < pNum; i++) {
				add(rax, sf.p[i]);
			}
		}
	};
	static const int apxFlagCombos[] = {
		UsePUSH2,
		UsePPX,
		UsePUSH2 | UsePPX,
		UseR30R31,
		UseR30R31 | UsePUSH2 | UsePPX,
	};
	static const uint8_t stackSizeTbl[] = { 0, 33 };
	for (size_t ai = 0; ai < sizeof(apxFlagCombos)/sizeof(apxFlagCombos[0]); ai++) {
		const int apxFlags = apxFlagCombos[ai];
		// Limit pNum/tNum/useRegs to a representative subset to keep the golden file small.
		for (int pNum = 0; pNum <= 2; pNum++) {
			for (int tNum = 0; tNum <= 4; tNum++) {
				// First 16 useRegs combos (bits 0..3: UseRCX, UseRDX, UseRSI, UseRDI)
				for (int i = 0; i < 16; i++) {
					int totalNum = pNum + tNum;
					int useRegs = apxFlags;
					if (i & 1) { useRegs |= UseRCX; totalNum++; }
					if (i & 2) { useRegs |= UseRDX; totalNum++; }
					if (i & 4) { useRegs |= UseRSI; totalNum++; }
					if (i & 8) { useRegs |= UseRDI; totalNum++; }
					// UseR30R31 doesn't consume any of the 14 managed slots (r30/r31 are
					// outside StackFrame's allocation table); this accounting is only a
					// heuristic to keep the golden file from growing too large.
					if (useRegs & UseR30R31) totalNum += 2;
					if (totalNum > 14) continue;
					for (size_t j = 0; j < sizeof(stackSizeTbl)/sizeof(stackSizeTbl[0]); j++) {
						int stackSizeByte = stackSizeTbl[j];
						Code c(pNum, tNum, useRegs, stackSizeByte);
						Data d;
						d.paramId.pNum = pNum;
						d.paramId.tNum = tNum;
						d.paramId.useRegs = useRegs;
						d.paramId.stackSizeByte = stackSizeByte;
						d.code.assign(c.getCode(), c.getCode() + c.getSize());
						dataMap[d.paramId.id()] = d;
#ifndef DUMP
						// APX instructions (push2, push2p, pushp etc.) require APX_F; skip execution otherwise.
						static const bool hasApx = Xbyak::util::Cpu().has(Xbyak::util::Cpu::tAPX_F);
						if (!hasApx) continue;
						switch (pNum) {
						case 0:
							{
								int (*f)() = c.getCode<int (*)()>();
								CYBOZU_TEST_EQUAL(0, f());
								break;
							}
						case 1:
							{
								int (*f1)(int) = c.getCode<int (*)(int)>();
								CYBOZU_TEST_EQUAL(1, f1(1));
								break;
							}
						case 2:
							{
								int (*f2)(int, int) = c.getCode<int (*)(int, int)>();
								CYBOZU_TEST_EQUAL(11, f2(1, 10));
								break;
							}
						}
#endif
					}
				}
			}
		}
	}
#ifdef DUMP
	for (DataMap::const_iterator it = dataMap.begin(); it != dataMap.end(); ++it) {
		const Data& d = it->second;
		printf("static const uint8_t apx_code_%" PRIx64 "[] = {\n", d.paramId.id());
		for (size_t j = 0; j < d.code.size(); j++) {
			if (j % 16 == 0) {
				if (j > 0) printf("\n");
				printf("\t");
			}
			if (j > 0) printf(" ");
			printf("0x%02x,", d.code[j]);
		}
		printf("\n};\n");
	}
	printf("static const struct {\n");
	printf("\tuint64_t paramId;\n");
	printf("\tconst uint8_t *code;\n");
	printf("\tsize_t codeSize;\n");
	printf("} g_apxDataVec[] = {\n");
	for (DataMap::const_iterator it = dataMap.begin(); it != dataMap.end(); ++it) {
		const Data& d = it->second;
		printf("\t{ 0x%" PRIx64 ", apx_code_%" PRIx64 ", %zu },\n", d.paramId.id(), d.paramId.id(), d.code.size());
	}
	printf("};\n");
#else
	DataMap dataMapExpected;
	for (size_t i = 0; i < sizeof(g_apxDataVec) / sizeof(*g_apxDataVec); i++) {
		const uint64_t id = g_apxDataVec[i].paramId;
		Data d;
		d.paramId.set_id(id);
		d.code.assign(g_apxDataVec[i].code, g_apxDataVec[i].code + g_apxDataVec[i].codeSize);
		dataMapExpected[id] = d;
	}
	CYBOZU_TEST_EQUAL(dataMap.size(), dataMapExpected.size());
	for (DataMap::const_iterator it = dataMapExpected.begin(); it != dataMapExpected.end(); ++it) {
		const uint64_t id = it->first;
		DataMap::const_iterator it2 = dataMap.find(id);
		CYBOZU_TEST_ASSERT(it2 != dataMap.end());
		const Data& d = it2->second;
		const Data& dExpected = it->second;
		CYBOZU_TEST_EQUAL(d.code.size(), dExpected.code.size());
		CYBOZU_TEST_EQUAL_ARRAY(d.code.data(), dExpected.code.data(), d.code.size());
	}
#endif
}

#ifdef DUMP
int main()
{
	stackFrameTest();
	apxStackFrameTest();
}
#else
CYBOZU_TEST_AUTO(stackFrame)
{
	stackFrameTest();
}
CYBOZU_TEST_AUTO(stackFrameApx)
{
	apxStackFrameTest();
}
#endif
