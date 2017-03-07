TARGET = HELIOS

BUILD = build/

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

build:$(BUILD)/kernel.elf
	cp src/kernel/kernel.elf $(BUILD)

$(TARGET).iso:
	make build
	grub-mkrescue -o $@ $(BUILD)

