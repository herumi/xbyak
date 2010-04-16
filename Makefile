PREFIX=/usr/local
INSTALL_DIR=$(PREFIX)/include/xbyak

all:
	make -C sample

clean:
	make -C sample clean

install:
	mkdir -p $(INSTALL_DIR)
	cp -pR xbyak/*.h $(INSTALL_DIR)

uninstall:
	rm -i $(INSTALL_DIR)/*.h
	rmdir $(INSTALL_DIR)

