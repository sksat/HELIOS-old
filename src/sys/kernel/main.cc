#include "../boot/multiboot2.h"
#include "asmfunc.h"
#include "dev/screen.h"
#include "dev/qemu_vga.h"

extern char hankaku[4096];

class Tty : public ScrnCtl {
public:
	Tty();
	void putchar(int x, int y, char col, char c);
	void putchar(char c);
	void puts(char* str);
	void _PutPixel(unsigned char, int, int){}
protected:
	char* font;
	int font_x, font_y;
	int x, y;
private:
	void putfont8(int x, int y, char col, char *font);
};

Tty::Tty(){
	font = (char*)hankaku;
	font_x = 8;
	font_y = 16;
}

void Tty::putchar(int x, int y, char col, char c){
	if(font == nullptr) return;
	if(font == (char*)hankaku){
		if(c*16 >= 4096) return;
		putfont8(x, y, col, font+c*16);
	}
	return;
}

void Tty::putchar(char c){
	x += font_x;
	if(x >= scrnx){
		x = 0;
		y += font_y;
	}
	if(y >= scrny) y = 0;
	putchar(x, y, 15, c);
}

void Tty::puts(char *str){
	for(;;){
		putchar(*str);
		str++;
		if(*str == '\0') break;
	}
}

void Tty::putfont8(int x, int y, char col, char *font){
	char *p, d /* data */;
	vram = (char*)0xa0000;
	for(int i=0; i<16; i++){
		p = vram + (y+i) * scrnx + x;
		d = font[i];
		unsigned char k = 0x80;
		for(int j=0; j<8; j++){
			if((d & k) != 0) { p[j] = col; }
			k = k/2;
		}
	}
	return;
}


int main(void){
	QemuVgaCtl vga_ctl;
	vga_ctl.Init();
	vga_ctl.ChangeMode(800, 600, 8, 0);

	vga_ctl.BoxFill(15, 0, 0, 800, 600);
	for(int x=0;x<320;x++){
		for(int y=0;y<200;y++){
//			char* vram = (char*)0xa0000;
//			vram[320*y+x] = 15;
//			vga_ctl._PutPixel(15,x,y);
		}
	}

	Tty tty;
	tty.putchar(100,100,15,'A');
	tty.putchar(100,110,15,'B');
	tty.puts("abyaaaaaaaaaaaaaaaaaaaaaaaaaahogeeeeeeeeeeeeeeeeeeeeeeeeee");
/*
	for(int i=0xa0000;i<=0xaffff;i++){
		char *p;
		p = (char*)i;
		*p = i & 0x0f;
	}
*/
	for(;;);
}


