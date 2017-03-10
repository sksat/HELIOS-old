#define ASMi_FILE
#include "multiboot2.h"

#define MULTIBOOTHEADER_SIZE (multiboot2_header_end - multiboot2_header)

.global entry
.code32
.section .boot

.balign 8

entry:
	jmp start

multiboot2_header:
	.long MULTIBOOT2_HEADER_MAGIC
	.long MULTIBOOT_ARCHITECTURE_i386
	.long MULTIBOOTHEADER_SIZE
	.long -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_i386 + MULTIBOOTHEADER_SIZE)

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

start:
	hlt
	jmp start	// loop

