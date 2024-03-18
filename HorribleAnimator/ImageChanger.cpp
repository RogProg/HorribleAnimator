#include "framework.h"
#include "ImageChanger.h"


ImageChanger::ImageChanger(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {

	starth= 0;

}


void ImageChanger::resize(int _x ,int _y , int size) {



	sw = (int)ceil(sqrt(size));

	if (sw < 2) sw = 2;

	sh = (int)ceil((double)size / sw);
	
	if ((int)(mainwindow->MyDxstuff->size.height - 42 * 2 - 26 * 2) < (int)(sh * 100)) {

		sh = (mainwindow->MyDxstuff->size.height - 42 * 2 - 26 * 2) / 100;

		sw = (int)ceil((double)size * sh);

	}

	
	if ((int)(mainwindow->MyDxstuff->size.width) < (int)(sw * 100)) {

		sw = (mainwindow->MyDxstuff->size.width) / 100;

	}
	

	int tmpw = sw * 100 + 20;
	int tmph = sh * 100 + 42 * 2 + 16 * 2;
	

	if ((int)mainwindow->MyDxstuff->size.width < (int)(_x + tmpw)) {

		_x = mainwindow->MyDxstuff->size.width - tmpw;

	}

	if ((int)mainwindow->MyDxstuff->size.height < (int)(_y + tmph)) {

		_y = (mainwindow->MyDxstuff->size.height - tmph);

	}


	BaseWindow::resize(_x, _y, tmpw, tmph);

}



void ImageChanger::paint() {

	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 160, 160, 160);


	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 0, 0, w - 1, h - 1, 0, 0, 0);



	int th = starth;

	int xx = 0;
	int yy = 0;

	for (int i = 0; i < sw*sh; i++) {

		if (th < mainwindow->MyDxstuff->arr.size()) {

			mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 10+xx*100 , 42 + 16 + yy*100, 80,80,200, 200, 200);
			mainwindow->MyDxstuff->drawbitmapscaleQuick(lmem, w, h, i, (imagedata*)mainwindow->MyDxstuff->arr[th], 10 + xx * 100, 42 + 16 + yy * 100, 1.0);
			mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 10 + xx * 100, 42 + 16 + yy * 100, 10 + xx * 100 + 80, 42 + 16 + yy * 100 + 80, 0, 0, 0);

		}

		th++;

		xx++;
		if (xx >= sw) {

			xx = 0;

			yy++;

		}

	}

	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->upimg, w/2 - 150/2, 5, 1.0);
	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->downimg, w/2 - 150/2, h - 42 - 5, 1.0);

}

void ImageChanger::mouseclick(int mox, int moy) {

	selected = -1;

	mox -= x;
	moy -= y;

	xx = 0;
	yy = 0;

	int th = starth;

	for (int i = 0; i < sw*sh; i++) {


		if ((mox > (10 + xx * 100)) && (moy > (42 + 16 + yy * 100)) && (mox < (10 + xx * 100 + 80)) && (moy < (42 + 16 + yy * 100 + 80))) {

			if (th < mainwindow->MyDxstuff->arr.size()) {

				selected = th;

				return;

			}

		}

		th++;

		xx++;
		if (xx >= sw) {

			xx = 0;

			yy++;

		}

	}
	
	if ((mox > (w / 2 - 150 / 2)) && (moy > 5) && (mox < (w / 2 + 150 / 2)) && (moy < (5 + 42))) {

		if (starth > 0) starth -= sw;

		return;

	}

	if ((mox > (w / 2 - 150 / 2)) && (moy > (h-42 - 5) && (mox < (w / 2 + 150 / 2)) && (moy < (h-5)))) {

		if ((starth + sw*sh) < mainwindow->MyDxstuff->arr.size()) starth += sw;

		return;

	}

	
}

void ImageChanger::mouseup(int mox, int moy) {

	
	mox -= x;
	moy -= y;

	if (!((mox > 0) && (moy > 0) && (mox < w) && (moy < h))) {

		mainwindow->imagechangerup = false;

		return;

	}


	

	if (selected != -1) {


		if (source == AINIMATIONWINDOWSENDER) {

			mainwindow->MyAnimationWindow->changeImage(selected);

		}

		if (source == NEWBACKGROUNDSENDER) {

			mainwindow->MyAnimationWindow->changeBackground(selected);

		}

		if (source == OBJECTWINSENDER) {

			mainwindow->MyObjectWindow->changeImage(selected);

		}


		

		mainwindow->imagechangerup = false;

	}


}