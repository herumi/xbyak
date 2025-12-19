#include <xbyak/xbyak_cpucache.h>

int main()
{
	Xbyak::util::intel::CpuCache cpuCache;
	if (!cpuCache.init()) {
		puts("cpuCache.init err");
	}
	cpuCache.put();
}
