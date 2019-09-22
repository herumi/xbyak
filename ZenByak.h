#include "xbyak/xbyak.h"

namespace Zen {
    class CodeGenerator : public Xbyak::CodeGenerator {
    public:
        void monitorx() { db(0x0F); db(0x01); db(0xFA); }
        void mwaitx() { db(0x0F); db(0x01); db(0xFB); }
        void clzero() { db(0x0F); db(0x01); db(0xFC); }
    };
};


