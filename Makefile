TARGET = HELIOS

BUILD_DIR = build/

FDIMG	= HELIOS.img
ISO	= HELIOS.iso

CDSIZE	= 512

%.o:%.c
	gcc -c $<

default:
	make iso

run:
	make qemurun

qemurun:
	make qemurun_iso

qemurun_iso:
	make iso
	qemu-system-x86_64 -drive format=raw,file=$(TARGET).iso

fdimg:
	dd if=/dev/zero of=$(FDIMG) bs=1k count=1440
	mkdosfs $(FDIMG)
	$(eval DISK_FILE := $(FDIMG))
	make build

cdimg:
	dd if=/dev/zero of=$(ISO) bs=1M count=$(CDSIZE)
	mkdosfs $(ISO)
	$(eval DISK_FILE := $(ISO))
	make build

build:
	mkdir $(BUILD_DIR)
	sudo losetup /dev/loop0 $(DISK_FILE)
	mkfs -t vfat /dev/loop0
	sudo mount -t vfat /dev/loop0 /mnt/HELIOS
	make -C src build BUILD_DIR=/mnt/HELIOS
	sudo umount /mnt/HELIOS
	losetup -d /dev/loop0
	rm -r $(BUILD_DIR)

clean:
	rm -r $(BUILD_DIR)

