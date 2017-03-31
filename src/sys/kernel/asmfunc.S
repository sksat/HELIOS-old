.intel_syntax noprefix

.global _io_hlt, _io_cli, _io_sti, _io_stihlt
.global _io_in8, _io_in16, _io_in32
.global _io_out8, io_out16, _io_out32

.text
.code32

_io_hlt:
	hlt
	ret

_io_cli:
	cli
	ret

_io_sti:
	sti
	ret

_io_stihlt:
	sti
	hlt
	ret

_io_in8:	// int io_in8(int port)
	mov	edx, [esp+4]
	mov	eax, 0
	in	al,dx
	ret

_io_in16:
	mov	edx, [esp+4]
	mov	eax, 0
	in	ax,dx
	ret

_io_in32:
	mov	edx, [esp+4]
	in	eax, dx
	ret

_io_out8:	// void io_out8(int port, int data)
	mov	edx, [esp+4]
	mov	al, [esp+8]
	out	dx, al
	ret

io_out16:
	mov	edx, [esp+4]
	mov	eax, [esp+8]
	out	dx, ax
	ret

_io_out32:
	mov	edx, [esp+4]
	mov	eax, [esp+8]
	out	dx, eax
	ret
