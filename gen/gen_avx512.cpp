#define XBYAK_DONT_READ_LIST
#include <stdio.h>
#include <string.h>
#include "../xbyak/xbyak.h"
#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak;
#ifdef _MSC_VER
	#pragma warning(disable : 4996) // scanf
	#define snprintf _snprintf_s
#endif

// QQQ : copy CodeGenerator
enum {
	PP_NONE = 1 << 0,
	PP_66 = 1 << 1,
	PP_F3 = 1 << 2,
	PP_F2 = 1 << 3,
	MM_0F = 1 << 5,
	MM_0F38 = 1 << 6,
	MM_0F3A = 1 << 7,
	VEX_L0 = 1 << 8,
	VEX_L1 = 1 << 9
};

const int NONE = 256; // same as Xbyak::CodeGenerator::NONE

std::string type2String(int type)
{
	std::string str;
	if (type & MM_0F) {
		str = "MM_0F";
	} else if (type & MM_0F38) {
		str = "MM_0F38";
	} else if (type & MM_0F3A) {
		str = "MM_0F3A";
	}
	if (type & PP_66) {
		str += " | PP_66";
	} else if (type & PP_F3) {
		str += " | PP_F3";
	} else if (type & PP_F2) {
		str += " | PP_F2";
	}
	if (type & VEX_L0) {
		str += " | VEX_L0";
	} else if (type & VEX_L1) {
		str += " | VEX_L1";
	}
	return str;
}

void putOpmask()
{
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "kadd", 0x4A },
			{ "kand", 0x41 },
			{ "kandn", 0x42 },
			{ "kor", 0x45 },
			{ "kxnor", 0x46 },
			{ "kxor", 0x47 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | T_W1, 0x%02X); }\n", p.name, p.code);
			printf("void %sb(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66 | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66 | T_W1, 0x%02X); }\n", p.name, p.code);
		}
		printf("void kunpckbw(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | PP_66 | T_W0, 0x4B); }\n");
		printf("void kunpckwd(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | T_W0, 0x4B); }\n");
		printf("void kunpckdq(const Opmask& r1, const Opmask& r2, const Opmask& r3) { opVex(r1, &r2, r3, VEX_L1 | MM_0F | T_W1, 0x4B); }\n");
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "knot", 0x44 },
			{ "kortest", 0x98 },
			{ "ktest", 0x99 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | T_W1, 0x%02X); }\n", p.name, p.code);
			printf("void %sb(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66 | T_W0, 0x%02X); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2) { opVex(r1, 0, r2, MM_0F | PP_66 | T_W1, 0x%02X); }\n", p.name, p.code);
		}
	}
	{
		const struct Tbl {
			const char *name;
			uint8 code;
		} tbl[] = {
			{ "kshiftl", 0x32 },
			{ "kshiftr", 0x30 },
		};
		for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
			const Tbl& p = tbl[i];
			printf("void %sw(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A | T_W1, 0x%02X, imm); }\n", p.name, p.code);
			printf("void %sq(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A | T_W1, 0x%02X, imm); }\n", p.name, p.code + 1);
			printf("void %sb(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A | T_W0, 0x%02X, imm); }\n", p.name, p.code);
			printf("void %sd(const Opmask& r1, const Opmask& r2, uint8 imm) { opVex(r1, 0, r2, PP_66 | MM_0F3A | T_W0, 0x%02X, imm); }\n", p.name, p.code + 1);
		}
	}
	puts("void kmovw(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | T_W0, 0x90); }");
	puts("void kmovq(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | T_W1, 0x90); }");
	puts("void kmovb(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | PP_66 | T_W0, 0x90); }");
	puts("void kmovd(const Opmask& k, const Operand& op) { opVex(k, 0, op, VEX_L0 | MM_0F | PP_66 | T_W1, 0x90); }");

	puts("void kmovw(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | T_W0, 0x91); }");
	puts("void kmovq(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | T_W1, 0x91); }");
	puts("void kmovb(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | PP_66 | T_W0, 0x91); }");
	puts("void kmovd(const Address& addr, const Opmask& k) { opVex(k, 0, addr, VEX_L0 | MM_0F | PP_66 | T_W1, 0x91); }");

	puts("void kmovw(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F | T_W0, 0x92); }");
	puts("void kmovw(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | T_W0, 0x93); }");
	puts("#ifdef XBYAK64");
	puts("void kmovq(const Opmask& k, const Reg64& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_F2 | T_W1, 0x92); }");
	puts("void kmovq(const Reg64& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_F2 | T_W1, 0x93); }");
	puts("#endif");
	puts("void kmovb(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_66 | T_W0, 0x92); }");
	puts("void kmovb(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_66 | T_W0, 0x93); }");
	puts("void kmovd(const Opmask& k, const Reg32& r) { opVex(k, 0, r, VEX_L0 | MM_0F | PP_F2 | T_W0, 0x92); }");
	puts("void kmovd(const Reg32& r, const Opmask& k) { opVex(r, 0, k, VEX_L0 | MM_0F | PP_F2 | T_W0, 0x93); }");
}

int main()
{
	puts("#ifdef XBYAK_AVX512");
	putOpmask();
	puts("#endif");
}
