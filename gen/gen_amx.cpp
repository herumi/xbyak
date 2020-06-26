#define XBYAK_DONT_READ_LIST
#include <stdio.h>
#include <string.h>
#include "../xbyak/xbyak.h"

using namespace Xbyak;
#ifdef _MSC_VER
	#pragma warning(disable : 4996) // scanf
	#define snprintf _snprintf_s
#endif

#include "avx_type.hpp"

void putAMX_TILE()
{
    puts("void ldtilecfg(const Address& addr) { opAMX(tm0, tm0, addr, T_0F38 | T_W0 | T_TMM, 0x49); }");
    puts("void sttilecfg(const Address& addr) { opAMX(tm0, tm0, addr, T_66 | T_0F38 | T_W0 | T_TMM, 0x49); }");
    puts("void tileloadd(const Tmm& tm, const Operand& op) { opAMX(tm, tm0, op, T_F2 | T_0F38 | T_W0 | T_TMM, 0x4b); }");
    puts("void tileloaddt1(const Tmm& tm, const Operand& op) { opAMX(tm, tm0, op, T_66 | T_0F38 | T_W0 | T_TMM, 0x4b); }");
    puts("void tilerelease() { db(0xc4); db(0xe2); db(0x78); db(0x49); db(0xc0); }");
    puts("void tilestored(const Operand& op, const Tmm& tm) { opAMX(tm, tm0, op, T_F3 | T_0F38 | T_W0 | T_TMM, 0x4b); }");
    puts("void tilezero(const Tmm& Tmm) { opAMX(Tmm, tm0, tm0, T_F2 | T_0F38 | T_W0 | T_TMM, 0x49); }");
}
void putAMX_INT8()
{
    puts("void tdpbssd(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opAMX(x1, x3, x2, T_F2 | T_0F38 | T_W0 | T_TMM, 0x5e); }");
    puts("void tdpbsud(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opAMX(x1, x3, x2, T_F3 | T_0F38 | T_W0 | T_TMM, 0x5e); }");
    puts("void tdpbusd(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opAMX(x1, x3, x2, T_66 | T_0F38 | T_W0 | T_TMM, 0x5e); }");
    puts("void tdpbuud(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opAMX(x1, x3, x2,        T_0F38 | T_W0 | T_TMM, 0x5e); }");
}
void putAMX_BF16()
{
    puts("void tdpbf16ps(const Tmm& x1, const Tmm& x2, const Tmm& x3) { opAMX(x1, x3, x2, T_F3 | T_0F38 | T_W0 | T_TMM, 0x5c); }");
}

int main()
{
	putAMX_TILE();
	putAMX_INT8();
	putAMX_BF16();
}
