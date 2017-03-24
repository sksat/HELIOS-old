TARGET = HELIOS

BUILD_DIR = build/

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

iso:
	make $(TARGET).iso

build:
	make -C src build BUILD_DIR=$(BUILD_DIR)

$(TARGET).iso:
	make build
	grub-mkrescue -o $@ $(BUILD)

