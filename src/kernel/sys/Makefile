DEPTH = ../../../
include ../../com_mak.txt

SYS	= HELIOS.sys
SYS_OBJS= main.obj
LDSCRIPT= kernel.ld

default	:
	make $(SYS)

$(SYS)	: $(SYS_OBJS)
	ld -T $(LDSCRIPT) -Map kernel.map -nostdlib --oformat binary -o $@ $^


