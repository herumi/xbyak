#include "lib.h"
#include <xbyak/xbyak.h>

struct Code : public Xbyak::CodeGenerator {
	Code()
	{
		printf("Code:%s\n", eax.toString());
		ret();
	}
};

void init()
	try
{
	static bool init = true;
	printf("in lib_test %d\n", init);
	if (!init) return;
	init = false;
	static Code code;
} catch (const Xbyak::Error& e) {
	printf("err=%s\n", Xbyak::ConvertErrorToString(e));
}

