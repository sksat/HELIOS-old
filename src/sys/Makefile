DEPTH = ../../
include ../com_mak.txt

export

default:
	make build

ipl:
	make -C boot ipl

build:
	make -C boot build
	make -C kernel build

clean:
	make -C boot clean
	make -C kernel clean
