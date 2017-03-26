TARGET = HELIOS

BUILD_DIR := build/
MBR_BIN	= $(BUILD_DIR)boot/mbr.bin
BUILDED_FILES = $(wildcard $(BUILD_DIR)*.a)

FDIMG	:= HELIOS.img
CDIMG	:= HELIOS.iso

export

default:
	make fdimg

run:
	make qemurun

qemurun:
	make qemurun_fdimg

qemurun_fdimg:
	make fdimg
	qemu-system-x86_64 -fda $(FDIMG)

qemurun_cdimg:
	make cdimg
	qemu-system-x86_64 -drive format=raw,file=$(CDIMG)

img:
	make fdimg

fdimg:
	$(eval DISK_TYPE := fd)
	$(eval DISK_FILE := $(FDIMG))
	make build
	make $(FDIMG)

cdimg:
	$(eval DISK_TYPE := cd)
	$(eval DISK_FILE := $(CDIMG))
	$(eval GRUB := grub)
	make build
	make $(CDIMG)

$(FDIMG):$(MBR_BIN)
	sh disk.sh $(DISK_FILE) create $(DISK_TYPE)
	sh disk.sh $(DISK_FILE) addmbr $(MBR_BIN)
	sh disk.sh $(DISK_FILE) adddir $(BUILD_DIR)

$(CDIMG):$(BUILD_DIR)
	grub-mkrescue -o $(DISK_FILE) $(BUILD_DIR)

build:
	mkdir $(BUILD_DIR)
	echo "hoge" > build/a
	echo "fuga" > build/b
	make -C src build

clean:
	make -C src clean
	rm -fr $(BUILD_DIR)
	rm -f $(FDIMG) $(CDIMG)

full:
	make clean
	make
