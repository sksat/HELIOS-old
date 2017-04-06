#ifndef SCREEN_H_
#define SCREEN_H_

class ScrnCtl {
public:
	// void Init();
	char* GetVramAddr() {return vram; }
	void PutPixel(unsigned char col, int x, int y);
	void BoxFill(unsigned char col, int x0, int y0, int x1, int y1);
protected:
	static char *vram;
	static int scrnx, scrny, bit;
	static ScrnCtl *ctl;
	virtual void _PutPixel(unsigned char col, int x, int y) = 0;
//	static void (*PutPixel)(SCRN_INFO *info, int x, int y, unsigned char col);
};


#endif
