DEPTH = ../../../
include ../../com_mak.txt

IPL_BIN	= ipl/ipl.bin
MBR_BIN	= mbr.bin

GRUB_CFG= grub/grub.cfg

default:
	make ipl

build:
	$(info --------- SET BOOT ---------)
	$(info $(BOOTMODE))
ifdef GRUB
	$(info BOOT-MODE : GRUB)
	mkdir -p $(DEPTH)$(BUILD_DIR)boot/grub
	make build_grub
else
	$(info BOOT-MODE : IPL )
	mkdir $(DEPTH)$(BUILD_DIR)boot
	make build_ipl
endif
	$(info ----------------------------)

build_ipl:
	make -C ipl build
	cp $(IPL_BIN) $(MBR_BIN)
	cp $(MBR_BIN) $(DEPTH)$(BUILD_DIR)boot/

build_grub:
	$(warning there is no MBR)
	cp $(GRUB_CFG) $(DEPTH)$(BUILD_DIR)boot/grub/

clean:
	make -C ipl clean
	rm -f $(MBR_BIN)
