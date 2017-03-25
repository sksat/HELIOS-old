DEPTH = ../../../
include ../../com_mak.txt

IPL_SRC	= ipl.nask
IPL_BIN	= ipl.bin

MBR_BIN	= mbr.bin

default:
	make ipl

ipl : 
	make $(IPL_BIN)

grub :
	$(info sorry)

build:
	mkdir $(DEPTH)$(BUILD_DIR)boot
	make build_ipl
	cp $(MBR_BIN) $(DEPTH)$(BUILD_DIR)boot/

build_ipl:
	make ipl
	cp $(IPL_BIN) $(MBR_BIN)
