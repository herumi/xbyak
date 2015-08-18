#define XBYAK_NO_OP_NAMES
#include <xbyak/xbyak.h>
/*
dump of vc

0000000000450000 F3 0F C2 05 77 00 00 00 00 cmpeqss     xmm0,dword ptr [450080h]
0000000000450009 F7 05 6D 00 00 00 21 00 00 00 test        dword ptr [450080h],21h
0000000000450013 0F BA 25 65 00 00 00 03 bt          dword ptr [450080h],3
000000000045001B C4 E3 79 0D 05 5B 00 00 00 03 vblendpd    xmm0,xmm0,xmmword ptr [450080h],3
0000000000450025 C4 E3 79 0F 05 51 00 00 00 04 vpalignr    xmm0,xmm0,xmmword ptr [450080h],4
000000000045002F C4 E3 7D 19 1D 47 00 00 00 0C vextractf128 xmmword ptr [450080h],ymm3,0Ch
0000000000450039 C4 E3 75 46 05 3D 00 00 00 0D vperm2i128  ymm0,ymm1,ymmword ptr [450080h],0Dh
0000000000450043 C4 E3 79 1D 15 33 00 00 00 2C vcvtps2ph   mmword ptr [450080h],xmm2,2Ch
000000000045004D C7 05 29 00 00 00 34 12 00 00 mov         dword ptr [450080h],1234h
0000000000450057 C1 25 22 00 00 00 03 shl         dword ptr [450080h],3
000000000045005E D1 2D 1C 00 00 00    shr         dword ptr [450080h],1
0000000000450064 48 0F A4 05 13 00 00 00 03 shld        qword ptr [450080h],rax,3
000000000045006D 48 6B 05 0B 00 00 00 15 imul        rax,qword ptr [450080h],15h
0000000000450075 C4 E3 FB F0 05 01 00 00 00 15 rorx        rax,qword ptr [450080h],15h
000000000045007F C3                   ret
0000000000450080 F0 DE BC 9A 78 56 34 12
*/
struct Code : Xbyak::CodeGenerator {
	Code()
	{
		Xbyak::Label label;
		cmpss(xmm0, ptr[rip + label], 0);
		test(dword[rip + label], 33);
		bt(dword[rip + label ], 3);
		vblendpd(xmm0, dword[rip + label], 3);
		vpalignr(xmm0, qword[rip + label], 4);
		vextractf128(dword[rip + label], ymm3, 12);
		vperm2i128(ymm0, ymm1, qword[rip + label], 13);
		vcvtps2ph(ptr[rip + label], xmm2, 44);
		mov(dword[rip + label], 0x1234);
		shl(dword[rip + label], 3);
		shr(dword[rip + label], 1);
		shld(qword[rip + label], rax, 3);
		imul(rax, qword[rip + label], 21);
		rorx(rax, qword[rip + label], 21);
		ret();
	L(label);
		dq(0x123456789abcdef0ull);
	};
};

void dump(const unsigned char *p, size_t n)
{
	for (int i = 0; i < n; i++) {
		printf("%02x ", p[i]);
		if ((i % 16) == 15) putchar('\n');
	}
	putchar('\n');
}

int main()
{
	Code code;
	void (*f)() = code.getCode<void (*)()>();
	dump(code.getCode(), code.getSize());
	f();
}
