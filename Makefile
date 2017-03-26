TARGET = HELIOS

BUILD_DIR := build/
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

fdimg:
	$(eval DISK_TYPE := fd)
	$(eval DISK_FILE := $(FDIMG))
	make img
	make build

cdimg:
	$(eval DISK_TYPE := cd)
	$(eval DISK_FILE := $(CDIMG))
	make img
	make build

img:
	sh disk.sh $(DISK_FILE) create $(DISK_TYPE)

build:
	mkdir $(BUILD_DIR)
	echo "hoge" > build/a
	echo "fuga" > build/b
	make -C src build
ifeq ($(DISK_TYPE),fd)
	sh disk.sh $(DISK_FILE) addmbr $(BUILD_DIR)boot/mbr.bin
endif
	sh disk.sh $(DISK_FILE) adddir $(BUILD_DIR)

clean:
	make -C src clean
	rm -fr $(BUILD_DIR)
	rm -f $(FDIMG) $(CDIMG)

full:
	make clean
	make
