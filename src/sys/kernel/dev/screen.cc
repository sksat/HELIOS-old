#include "screen.h"

char* ScrnCtl::vram = 0x00;
int ScrnCtl::scrnx= 0;
int ScrnCtl::scrny= 0;
int ScrnCtl::bit  = 0;
ScrnCtl* ScrnCtl::ctl = nullptr;

void ScrnCtl::PutPixel(unsigned char col, int x, int y){
	ctl->_PutPixel(col, x, y);
}

void ScrnCtl::BoxFill(unsigned char col, int x0, int y0, int x1, int y1){
	if(ctl == nullptr) return;
	vram = (char*)0xa0000;
	for(int y=y0; y<=y1; y++){
		for(int x=x0; x<=x1; x++){
			vram[y * scrnx + x] = col;
			PutPixel(col, x, y);
		}
	}
}

