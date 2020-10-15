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

#include "avx_type.hpp"

void putVNNI(bool vexEncodingOnly)
{
	const struct Tbl {
		uint8_t code;
		const char *name;
		int type;
	} tbl[] = {
		{ 0x50, "vpdpbusd", T_66 | T_0F38 | T_YMM | T_EW0 | T_SAE_Z | T_B32},
		{ 0x51, "vpdpbusds", T_66 | T_0F38 | T_YMM | T_EW0 | T_SAE_Z | T_B32},

		{ 0x52, "vpdpwssd", T_66 | T_0F38 | T_YMM | T_EW0 | T_SAE_Z | T_B32},
		{ 0x53, "vpdpwssds", T_66 | T_0F38 | T_YMM | T_EW0 | T_SAE_Z | T_B32},
	};
	for (size_t i = 0; i < NUM_OF_ARRAY(tbl); i++) {
		const Tbl *p = &tbl[i];
		std::string type = type2String(p->type);
		printf("void %s(const Xmm& x1, const Xmm& x2, const Operand& op%s) { opAVX_X_X_XM(x1, x2, op, %s%s, 0x%02X, NONE%s); }\n"
			, p->name, !vexEncodingOnly ? ", preferred_encoding_t encoding = DEFAULT" : "", type.c_str()
			, !vexEncodingOnly ? " | T_PREF_EVEX" : "", p->code, !vexEncodingOnly ? ", encoding" : "");
	}
}

int main(int argc, char *[])
{
	bool vexEncodingOnly = argc == 2;
	putVNNI(vexEncodingOnly);
}
