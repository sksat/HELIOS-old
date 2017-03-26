DEPTH = ../../../
include ../../com_mak.txt

IPL_BIN	= ipl/ipl.bin
MBR_BIN	= mbr.bin

GRUB_CFG= grub/grub.cfg
BOOT_ELF= boot.elf

default:
	make ipl

build: $(BOOT_ELF)
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
	cp $(BOOT_ELF) $(DEPTH)$(BUILD_DIR)boot/
	$(info ----------------------------)

build_ipl:$(IPL_BIN)
	make -C ipl build
	cp $(IPL_BIN) $(MBR_BIN)
	cp $(MBR_BIN) $(DEPTH)$(BUILD_DIR)boot/

build_grub:$(GRUB_CFG)
	$(warning there is no MBR)
	cp $(GRUB_CFG) $(DEPTH)$(BUILD_DIR)boot/grub/

clean:
	make -C ipl clean
	rm -f $(MBR_BIN)

$(BOOT_ELF):boot.o
	ld -melf_i386 -Ttext=0x100000 $^ -o $@


