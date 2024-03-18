#include "framework.h"
#include "GfxTools.h"


GfxTools::GfxTools() {

	


};


void GfxTools::drawRect(byte* lmem, int w , int x,int y,int width,int heigth,  byte r, byte g, byte b) {


	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heigth; j++) {

			int ofs = (x + i + ( j + y)  * w) * 4;

			lmem[ofs] = r;
			lmem[ofs+1] = g;
			lmem[ofs+2] = b;
			lmem[ofs+3] = 255;


		}
	}

}

void GfxTools::drawVLine(byte* lmem, int w, int h , int x, int y, int y2, byte r, byte g, byte b) {

	if (x < 0) return;
	if (x >= w) return;

	if (y < 0) y = 0;
	if (y >= h) y = h - 1;

	if (y2 < 0) return;
	if (y2 >= h) y2 = h - 1;


	for (int j = y; j < y2; j++) {

		int ofs = (x + j * w) * 4;

		lmem[ofs] = r;
		lmem[ofs + 1] = g;
		lmem[ofs + 2] = b;
		lmem[ofs + 3] = 255;


	}
}

void GfxTools::drawHLine(byte* lmem, int w, int h, int x, int x2, int y, byte r, byte g, byte b) {

	if (y < 0) return;
	if (y >= h) return;

	if (x < 0) x = 0;
	if (x >= w) x = w - 1;

	if (x2 < 0) return;
	if (x2 >= w) x2 = w - 1;


	for (int i = x; i < x2; i++) {
		
			int ofs = (i + y * w) * 4;

			lmem[ofs] = r;
			lmem[ofs + 1] = g;
			lmem[ofs + 2] = b;
			lmem[ofs + 3] = 255;


		}

}

void GfxTools::drawBox(byte* lmem, int w, int h, int x, int y, int x2, int y2, byte r, byte g, byte b) {

	drawVLine(lmem, w, h, x, y, y2, r, g, b);
	drawVLine(lmem, w, h, x2, y, y2, r, g, b);

	drawHLine(lmem, w, h, x, x2, y, r, g, b);
	drawHLine(lmem, w, h, x, x2, y2, r, g, b);


}


void GfxTools::drawLine(byte* lmem, int w, int h, int x, int y, int x2, int y2, byte r, byte g, byte b) {


	if (abs(y2 - y) > abs(x2 - x)) {

		if (y > y2) {

			int tmpx = x;
			x = x2;
			x2 = tmpx;

			int tmpy = y;
			y = y2;
			y2 = tmpy;

		}

		double xx = x;

		double dx = (double)(x2 - x) / (y2 - y);


		int starty = y;
		if (starty < 0) {

			xx -= starty * dx;
			starty = 0;

		}

		int endy = y2;
		if (endy >= h) endy = h - 1;


		for (int py = starty; py < endy; py++) {

			int xxx = (int)floor(xx);

			if ((xxx >= 0) && (xxx < w)) {

				int ofs = (xxx + py * w) * 4;

				lmem[ofs] = r;
				lmem[ofs + 1] = g;
				lmem[ofs + 2] = b;

			}

			xx += dx;

		}

	} else {
		

		if (x > x2) {

			int tmpx = x;
			x = x2;
			x2 = tmpx;

			int tmpy = y;
			y = y2;
			y2 = tmpy;

		}

		double yy = y;

		double dy = (double)(y2 - y) / (x2 - x);

		int startx = x;
		if (startx < 0) {

			yy -= startx * dy;
			startx = 0;

		}

		int endx = x2;
		if (endx >= w) endx = w - 1;


		for (int px = startx; px < endx; px++) {

			int yyy = (int)floor(yy);

			if ((yyy >= 0) && (yyy < h)) {

				int ofs = (px + (yyy) * w) * 4;

				lmem[ofs] = r;
				lmem[ofs + 1] = g;
				lmem[ofs + 2] = b;
										
			}

			yy += dy;

		}


	}
	
}



