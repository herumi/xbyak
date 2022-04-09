
# Xbyak ![Badge Version] [![Badge License]][License] [![Badge Build]][Build Status]

*A C++ JIT assembler for `x86 (IA32)` , `x64(AMD64,x86-64)`*

<br>

---

<div align = 'center'>

**⸢ [Install] ⸥**  
**⸢ [Usage] ⸥**  
**⸢ [Changelog] ⸥**

</div>

---

<br>

## Abstract

Xbyak is a C++ header library that enables dynamically to assemble x86(IA32), x64(AMD64, x86-64) mnemonic.

The pronunciation of Xbyak is `kəi-bja-k`.
It is named from a Japanese word [開闢](https://translate.google.com/?hl=ja&sl=ja&tl=en&text=%E9%96%8B%E9%97%A2&op=translate), which means the beginning of the world.

## Feature
* header file only
* Intel/MASM like syntax
* fully support AVX-512

**Note**:
Use `and_()`, `or_()`, ... instead of `and()`, `or()`.
If you want to use them, then specify `-fno-operator-names` option to gcc/clang.

### News
- WAITPKG instructions (tpause, umonitor, umwait) are supported.
- MmapAllocator supports memfd with user-defined strings. see sample/memfd.cpp
- strictly check address offset disp32 in a signed 32-bit integer. e.g., `ptr[(void*)0xffffffff]` causes an error.
  - define `XBYAK_OLD_DISP_CHECK` if you need an old check, but the option will be remoevd.
- add `jmp(mem, T_FAR)`, `call(mem, T_FAR)` `retf()` for far absolute indirect jump.
- vnni instructions such as vpdpbusd supports vex encoding.
- (break backward compatibility) `push(byte, imm)` (resp. `push(word, imm)`) forces to cast `imm` to 8(resp. 16) bit.
- (Windows) `#include <winsock2.h>` has been removed from xbyak.h, so add it explicitly if you need it.
- support exception-less mode see. [Exception-less mode](#exception-less-mode)
- `XBYAK_USE_MMAP_ALLOCATOR` will be defined on Linux/macOS unless `XBYAK_DONT_USE_MMAP_ALLOCATOR` is defined.

### Supported OS

* Windows Xp, Vista, Windows 7, Windows 10(32bit, 64bit)
* Linux(32bit, 64bit)
* Intel macOS

### Supported Compilers

Almost C++03 or later compilers for x86/x64 such as Visual Studio, g++, clang++, Intel C++ compiler and g++ on mingw/cygwin.

## Author
MITSUNARI Shigeo(herumi@nifty.com)


<!----------------------------------------------------------------------------->

[Badge License]: https://img.shields.io/badge/License-BSD_3--Clause-blue.svg
[Badge Version]: https://img.shields.io/badge/Version_6.04-00B2FF
[Badge Build]: https://github.com/herumi/xbyak/actions/workflows/main.yml/badge.svg

[License]: COPYRIGHT

[Changelog]: Documentation/Changelog.md
[Install]: Documentation/Install.md
[Usage]: Documentation/Usage.md

[Build Status]: https://github.com/herumi/xbyak/actions/workflows/main.yml
