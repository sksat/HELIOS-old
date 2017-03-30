#define ASM_FILE
#include "../boot/multiboot2.h"

#define MULTIBOOTHEADER_SIZE (multiboot2_header_end - multiboot2_header)

.global entry

.code32
.section .boot

.balign 8

.extern _start
.extern main

multiboot2_header:
	.long MULTIBOOT2_HEADER_MAGIC
	.long MULTIBOOT_ARCHITECTURE_I386
	.long MULTIBOOTHEADER_SIZE
	.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + MULTIBOOTHEADER_SIZE)

align_tag_start:
	.short MULTIBOOT_HEADER_TAG_MODULE_ALIGN
		.short 0
		.long align_tag_end - align_tag_start
align_tag_end:

end_tag_start:
	.short MULTIBOOT_HEADER_TAG_END
	.short 0
	.long end_tag_end - end_tag_start
end_tag_end:

multiboot2_header_end:

.text
entry:
	cli
	%ebx, (multiboot_info)
	call main
	hlt
	jmp entry	// loop

.data
multiboot_info:
	.long 0
tmp_stack:
	.skip 32


