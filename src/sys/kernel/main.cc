#include "../boot/multiboot2.h"
#include "asmfunc.h"

class ScrnCtl {
public:
	void Init();
protected:
	static char *vram;
	static int scrnx, scrny, bit;
};

char* ScrnCtl::vram;
int ScrnCtl::scrnx	= 0;
int ScrnCtl::scrny	= 0;
int ScrnCtl::bit	= 0;

class QemuVgaCtl : public ScrnCtl {
public:
	QemuVgaCtl() {}
	void ChangeMode(int scrnx, int scrny, int bit, bool clear_flg);
private:
	bool IsCorrectArgs(int scrnx, int scrny, int bit);
	void SetQemuVgaReg(int reg, int data);
};

void ScrnCtl::Init(){
	vram = nullptr;
}

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
	if(clear_flg){
		flg = 0x41;
	}else{
		flg = 0xc1;
	}
	SetQemuVgaReg(0x0004, flg);

	this->scrnx = scrnx;
	this->scrny = scrny;
	this->bit   = bit;

	if((flg & 0x40) == 0){
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

int main(void){
	QemuVgaCtl vga_ctl;
	vga_ctl.ChangeMode(800, 600, 8, 1);

	for(;;);
}


