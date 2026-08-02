/*
	A minimal experiment for the static initialization order problem of a
	header-only library (modeled after xbyak.h) included from multiple
	translation units (lib_run.cpp and lib_test.cpp).
	lib.h contains
	- namespace-scope static references to function-local statics
	  (like the register constants of xbyak) : shared, the same address in all TUs
	- a static member of a class template (X::a) : a header-only idiom to share
	  a single instance
	- static Init s_init : exists per TU and runs init() at static initialization
	The first init() prints "a=0" because s_init of lib_test.cpp runs before
	the constructor of X::a; the initialization order across TUs is not
	guaranteed. Build with "make lib_run" (not a part of "make test") and
	inspect the output.
	Note: as of 2026-07-29, this crashes during static initialization when
	built with -O2 (g++ 14.2.0) and runs fine with -O0.
*/
#include "lib.h"

int main()
{
	puts("main");
	X::a.put();
	putReg();
}

