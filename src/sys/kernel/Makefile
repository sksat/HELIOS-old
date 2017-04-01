DEPTH = ../../../
include ../../com_mak.txt

SYS	= kernel.sys
SYS_OBJS= startup.o main.o asmfunc.o
SYS_OBJS+=font/hankaku.o
LDSCRIPT= kernel.ld

default	:
	make -C font
	make $(SYS)

$(SYS)	: $(SYS_OBJS)
	ld -melf_i386 -Ttext=0x100000 $^ -o $@

build:
	make
	cp $(SYS) $(DEPTH)$(BUILD_DIR)

clean:
	make -C font clean
	rm -f *.sys *.o
