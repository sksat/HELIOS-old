DEPTH = ../../
include ../com_mak.txt

KERNEL	= kernel.img

export

default:
	touch $(KERNEL)

ipl:
	make -C boot ipl

kernel:
	@echo 'hoge'

build:
	make -C boot build
	make -C sys build
