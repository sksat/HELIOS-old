#include "../boot/multiboot2.h"

#define VRAM_TEXTMODE	0x000B8000
#define MAX_X		80
#define COL_BLACK	0x00
#define COL_WHITE	0x0F


void puttext_vram(char *str, int len, int x, int y){
	unsigned short *vram_t, col;
	vram_t = (unsigned short*)VRAM_TEXTMODE;
	col = (COL_BLACK << 4) | (COL_WHITE & 0x0f);
	vram_t += x + y*MAX_X;
	for(int i=0;i<len;i++){
		vram_t++;
		*vram_t = (col << 8) | str[i];
	}
}

int main(void){
	char str[] = "welcome to HELIOS";
	char str2[]= "this is a simple baremetal program by sksat.";
	int len = sizeof(str);
	int len2= sizeof(str2);
	puttext_vram(str, len, 0, 0);
	puttext_vram(str2, len2, 0, 2);
	for(;;);
}


