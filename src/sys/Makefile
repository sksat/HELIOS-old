DEPTH = ../../
include ../com_mak.txt

KERNEL	= HELIOS.img

export

default:
	touch $(KERNEL)

ipl:
	make -C boot ipl

kernel:
	@echo 'hoge'

build:
	make -C boot build
	make -C kernel build

clean:
	make -C boot clean
	make -C kernel clean
	rm -f $(KERNEL)
