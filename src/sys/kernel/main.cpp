#include "../boot/multiboot2.h"
#include "asmfunc.h"

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

void set_qemuvga0reg(int reg, int dat)
{
    io_out16(0x01ce, reg);
    io_out16(0x01cf, dat);
    return;
}

char* init_qemuvga0(int x, int y, int c, int flag)
{
    set_qemuvga0reg(0x0004, 0x0000);
    set_qemuvga0reg(0x0001, x);
    set_qemuvga0reg(0x0002, y);
    set_qemuvga0reg(0x0003, c); /* 4, 8, 15, 16, 24, 32 */
    set_qemuvga0reg(0x0005, 0x0000);
    set_qemuvga0reg(0x0004, flag); /* リニアアクセスモードでVRAMの初期化をするなら0x41 */
        /* bit7 : VRAM初期化抑制, bit6 : リニアアクセスモード, bit0 : 設定有効 */
//    binfo->scrnx = x;
//    binfo->scrny = y;
//    binfo->vmode = c;
    if ((flag & 0x40) == 0) {
        return (char *) 0x000a0000;
    } else {
        return (char *) 0xe0000000;
    }
}

int main(void){
	char str[] = "welcome to HELIOS";
	char str2[]= "this is a simple baremetal program by sksat.";
	int len = sizeof(str);
	int len2= sizeof(str2);
	puttext_vram(str, len, 0, 0);
	puttext_vram(str2, len2, 0, 2);

	init_qemuvga0(800, 600, 8, 0xc1);

	for(;;);
}


