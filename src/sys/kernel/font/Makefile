DEPTH  =../../../../
include ../../../com_mak.txt

FONT_OBJ = hankaku.o

default:
	make $(FONT_OBJ)

clean:
	rm -f *.o *.bin

hankaku.o : hankaku.bin
	$(BIN2OBJ) $< $@ hankaku

hankaku.bin : hankaku.txt
	$(MAKEFONT) $< $@

