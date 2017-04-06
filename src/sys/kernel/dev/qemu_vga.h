#ifndef QEMU_VGA_H_
#define QEMU_VGA_H_

#include "screen.h"

class QemuVgaCtl : public ScrnCtl {
public:
	QemuVgaCtl() {}
	void Init();
	void ChangeMode(int scrnx, int scrny, int bit, bool clear_flg, int bank);
	void ChangeMode(int scrnx, int scrny, int bit, bool clear_flg);
	void _PutPixel(unsigned char col, int x, int y);
private:
	static int cur_bank;
	bool IsCorrectArgs(int scrnx, int scrny, int bit);
	void SetQemuVgaReg(int reg, int data);
};

#endif
