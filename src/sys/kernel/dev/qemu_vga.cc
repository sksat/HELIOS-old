#include "qemu_vga.h"
#include "../asmfunc.h"

int QemuVgaCtl::cur_bank = 0;

void QemuVgaCtl::Init(){
	ctl = this;
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
	ChangeMode(scrnx, scrny, bit, clear_flg, 0);
}

void QemuVgaCtl::ChangeMode(int scrnx, int scrny, int bit, bool clear_flg, int bank){
	char flg;
	if(!IsCorrectArgs(scrnx, scrny, bit)){
		return;
	}
	SetQemuVgaReg(0x0004, 0x0000);
	SetQemuVgaReg(0x0001, scrnx);
	SetQemuVgaReg(0x0002, scrny);
	SetQemuVgaReg(0x0003, bit);
	SetQemuVgaReg(0x0005, bank);
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

//	if((flg & 0x40) == 0){	// リニアアクセスモードじゃない
//		this->vram = (char*) 0xa0000;
//	}else{			// リニアアクセスモード(QEMUでは未実装)
		this->vram = (char*) 0xe0000000;
//	}

	return;
}

void QemuVgaCtl::SetQemuVgaReg(int reg, int dat){
	io_out16(0x01ce, reg);
	io_out16(0x01cf, dat);
}

void QemuVgaCtl::_PutPixel(unsigned char col, int x, int y){
	if(x > scrnx || y > scrny) return;

	int addr = y * scrnx + x;
	if(vram == (char*)0xe0000000){	// リニアアクセスモード
		vram[addr] = col;
		return;
	}

	int bank = 0;
	if(addr != 0){
//		bank = addr/(320*200);
		for(int i=1;;i++){
			if(addr > 0xffff*i){
				bank=i;
			}else{
				break;
			}
		}
	}
	if(bank != cur_bank){
		ChangeMode(scrnx, scrny, bit, 0, bank);
	}
	cur_bank = bank;
	addr -= bank * 0xffff;
//	vram = (char*)0xa0000;
	vram[addr] = col;
	return;
}


