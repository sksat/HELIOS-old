DEPTH = ../../../
include ../../com_mak.txt

SYS	= kernel.sys
SYS_OBJS= main.obj
LDSCRIPT= kernel.ld

default	:
	make $(SYS)

$(SYS)	: $(SYS_OBJS)
	ld -T $(LDSCRIPT) -Map kernel.map -nostdlib --oformat binary -o $@ $^

build:
	@echo "neko!w"
	make

clean:
	rm -f $(SYS)
