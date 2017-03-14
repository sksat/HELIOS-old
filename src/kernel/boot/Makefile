
%.o:%.c
	gcc -m32 -nostdlib -I. -c $<

#%.elf:%.S
#	gcc -m32 -I. -oformat=binary -nostdlib --entry=entry -Ttext 0x100000  $< -o $@

#%.o:%.S
#	gcc -I. -c $< -o $@

%.elf:%.o
	ld --oformat=binary --entry=entry -Ttext 0x100000 -o $@ $<
