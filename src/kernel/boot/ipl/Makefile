DEPTH	= ../../../
include ../../../com_mak.txt

default:
	make ipl.bin

ipl.bin:ipl.nask
	$(NASK) $< $@ $(<:.nask=.lst)
