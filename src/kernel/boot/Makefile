
%.o:%.c
	gcc -m32 -nostdlib -I. -c $<

%.elf:%.o
	ld --entry=entry --oformat=binary -Ttext 0x100000 -o $@ $<
