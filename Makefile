PREFIX?=/usr/local
INSTALL_DIR=$(PREFIX)/include/xbyak

all:
	$(MAKE) -C sample

clean:
	$(MAKE) -C sample clean

install:
	mkdir -p $(INSTALL_DIR)
	cp -pR xbyak/*.h $(INSTALL_DIR)

uninstall:
	rm -i $(INSTALL_DIR)/*.h
	rmdir $(INSTALL_DIR)

update:
	$(MAKE) -C gen

test:
	$(MAKE) -C test test

ref2cp:
	sed -i -E 's/const (Reg[0-9a-zA-Z]*|Mmx|Fpu|Xmm|Ymm|Zmm) ?& ?/\1 /g' xbyak/xbyak_mnemonic.h

.PHONY: test update
