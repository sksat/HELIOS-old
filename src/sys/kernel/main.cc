#include "../boot/multiboot2.h"
#include "asmfunc.h"

class ScrnCtl {
public:
	// void Init();
	char* GetVramAddr() {return vram; }
	void BoxFill(unsigned char col, int x0, int y0, int x1, int y1);
protected:
	static char *vram;
	static int scrnx, scrny, bit;
};

char* ScrnCtl::vram;
int ScrnCtl::scrnx	= 0;
int ScrnCtl::scrny	= 0;
int ScrnCtl::bit	= 0;

void ScrnCtl::BoxFill(unsigned char col, int x0, int y0, int x1, int y1){
//	vram = (char*)0x000a0000;
	for(int y=y0; y<=y1; y++){
		for(int x=x0; x<=x1; x++){
			vram[y * scrnx + x] = col;
		}
	}
}

class QemuVgaCtl : public ScrnCtl {
public:
	QemuVgaCtl() {}
	void ChangeMode(int scrnx, int scrny, int bit, bool clear_flg);
private:
	bool IsCorrectArgs(int scrnx, int scrny, int bit);
	void SetQemuVgaReg(int reg, int data);
};

bool QemuVgaCtl::IsCorrectArgs(int scrnx, int scrny, int bit){
	switch(scrnx){
	case 320:
	case 640:
	case 800:
	case 1024:
		break;
	default:
		return 0;
	}

	switch(scrny){
	case 200:
	case 240:
	case 400:
	case 480:
	case 600:
	case 768:
		break;
	default:
		return 0;
	}

	switch(bit){
	case 4:
	case 8:
	case 15:
	case 16:
	case 24:
	case 32:
		break;
	default:
		return 0;
	}
	return 1;
}

void QemuVgaCtl::ChangeMode(int scrnx, int scrny, int bit, bool clear_flg){
	char flg;
	if(!IsCorrectArgs(scrnx, scrny, bit)){
		return;
	}
	SetQemuVgaReg(0x0004, 0x0000);
	SetQemuVgaReg(0x0001, scrnx);
	SetQemuVgaReg(0x0002, scrny);
	SetQemuVgaReg(0x0003, bit);
	SetQemuVgaReg(0x0005, 0x0000);
	SetQemuVgaReg(0x0006, scrnx);
	SetQemuVgaReg(0x0007, scrny);
	SetQemuVgaReg(0x0008, 0x0000);
	SetQemuVgaReg(0x0009, 0x0000);
	if(clear_flg){
		flg = 0x41;
	}else{
		flg = 0xc1;
	}
	SetQemuVgaReg(0x0004, flg);

	this->scrnx = scrnx;
	this->scrny = scrny;
	this->bit   = bit;

	if((flg & 0x40) == 0){	// リニアアクセスモードじゃない
		this->vram = (char*) 0x000a0000;
	}else{
		this->vram = (char*) 0xe0000000;
	}

	return;
}

void QemuVgaCtl::SetQemuVgaReg(int reg, int dat){
	io_out16(0x01ce, reg);
	io_out16(0x01cf, dat);
}

extern char hankaku[4096];

class Tty : public ScrnCtl {
public:
	Tty(void) { font=(char*)hankaku; }
	void putchar(int x, int y, char col, char c);
protected:
	char* font;
private:
	void putfont8(int x, int y, char col, char *font);
};

void Tty::putchar(int x, int y, char col, char c){
	if(font == nullptr) return;
	if(font == (char*)hankaku){
//		if(c*16 >= 4096) return;
		putfont8(x, y, col, font+c*16);
	}
	return;
}

void Tty::putfont8(int x, int y, char col, char *font){
	char *p, d /* data */;
	vram = (char*)0xa0000;
	for(int i=0; i<16; i++){
		p = vram + (y+i) * scrnx + x;
		d = font[i];
		char k = 0x80;
		for(int j=0; j<8; j++){
			if((d & k) != 0) { p[j] = col; }
			k = k/2;
		}
	}
	return;
}

int main(void){
	QemuVgaCtl vga_ctl;
	vga_ctl.ChangeMode(800, 600, 8, 0);

	ScrnCtl scrn_ctl;
	for(int i=0;;i+=2){
		scrn_ctl.BoxFill(15, 0, 0, i, 0);
	}

	Tty tty;
	tty.putchar(100,100,15,'A');
/*
	for(int i=0xa0000;i<=0xaffff;i++){
		char *p;
		p = (char*)i;
		*p = i & 0x0f;
	}
*/
	for(;;);
}


