#include "framework.h"
#include "ObjectWindow.h"

ObjectWindow::ObjectWindow(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {

	selected = -1;

	frametext = (textdata*)malloc(sizeof(textdata));

	frametext->x = x + 25;
	frametext->y = y + h - 70;

	addtext(frametext);

	swprintf_s(frametext->text, 100, L"");

}

void ObjectWindow::resize(int _x, int _y, int _w, int _h) {

	BaseWindow::resize(_x, _y, _w, _h);

	frametext->x = x + 25;
	frametext->y = y + h - 70;

	find_number();

}


void ObjectWindow::find_number() {

	bh = (h - 42 * 2 - 10 - 82) / 100;

}

void ObjectWindow::addimage(imagedata* idata) {


	imagedata* id = new imagedata;

	id->data = idata->data;
	id->ch = idata->ch;
	id->w = idata->w;
	id->h = idata->h;
	id->id = (int)imagearr.size();

	id->sw = 80;
	id->sh = 80;

	imagearr.push_back(id);

	find_number();

}

void ObjectWindow::moveUp() {

	int find = -1;
	int inorder = -1;

	if ((mainwindow->MyAnimationWindow->imagearr.size() > 1)){ // && (mainwindow->MyAnimationWindow->imagearr[selected]->layer != (mainwindow->MyAnimationWindow->imagearr.size() - 1))) {
	
		for (int i = 0; i < mainwindow->MyAnimationWindow->imagearr.size(); i++) {

			if (mainwindow->MyAnimationWindow->imagearr[i]->scene == (mainwindow->MyAnimationWindow->imagearr[selected]->scene)) {

				if (mainwindow->MyAnimationWindow->imagearr[i]->layer > mainwindow->MyAnimationWindow->imagearr[selected]->layer) {

					find = i;

				}

				if (mainwindow->MyAnimationWindow->imagearr[i]->layer == (mainwindow->MyAnimationWindow->imagearr[selected]->layer + 1)) {

					inorder = i;

				}


			}

		}

		if (inorder != -1) find = inorder;

		if (find != -1) {
			int tmp = mainwindow->MyAnimationWindow->imagearr[selected]->layer;
			mainwindow->MyAnimationWindow->imagearr[selected]->layer = mainwindow->MyAnimationWindow->imagearr[find]->layer;;
			mainwindow->MyAnimationWindow->imagearr[find]->layer = tmp;

			

		}

	}

}

void ObjectWindow::moveDown() {

	int find = -1;
	int inorder = -1;

	if ((mainwindow->MyAnimationWindow->imagearr.size() > 1)){ // && (mainwindow->MyAnimationWindow->imagearr[selected]->layer != 0)) {

		for (int i = 0; i < mainwindow->MyAnimationWindow->imagearr.size(); i++) {

			if (mainwindow->MyAnimationWindow->imagearr[i]->scene == (mainwindow->MyAnimationWindow->imagearr[selected]->scene)) {

				if (mainwindow->MyAnimationWindow->imagearr[i]->layer < mainwindow->MyAnimationWindow->imagearr[selected]->layer) {

					find = i;

				}

				if (mainwindow->MyAnimationWindow->imagearr[i]->layer == (mainwindow->MyAnimationWindow->imagearr[selected]->layer - 1)) {

					inorder = i;

				}

			}

		}

		if (inorder != -1) find = inorder;

		if (find != -1) {

			int tmp = mainwindow->MyAnimationWindow->imagearr[selected]->layer;
			mainwindow->MyAnimationWindow->imagearr[selected]->layer = mainwindow->MyAnimationWindow->imagearr[find]->layer;;
			mainwindow->MyAnimationWindow->imagearr[find]->layer = tmp;

			

		}

	}

}



void ObjectWindow::paint() {

	find_number();

	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 100, 100, 100);
	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 0, 0, w-1, h-1, 20, 20, 20);

	int th = starth;

	int xx = 0;
	int yy = 0;

	for (int i = 0; i < bh*2; i++) {


		if ((th < mainwindow->MyAnimationWindow->imagearr.size())) {

	       if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {

				mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 10 + xx * 100, 42 + 10 + yy * 100, 80, 80, 180, 180, 180);

				mainwindow->MyDxstuff->drawbitmapscaleQuick(lmem, w, h, th, mainwindow->MyDxstuff->arr[mainwindow->MyAnimationWindow->imagearr[th]->imagelink], 10 + xx * 100, 10 + yy * 100 + 42, 1.0);

				mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 10 + xx * 100, 42 + 10 + yy * 100, 10 + xx * 100 + 80, 42 + 10 + yy * 100 + 80, 0, 0, 0);

		
			}

		

			if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {

				xx++;
				if (xx > 1) {
					xx = 0;
					yy++;

				}
			}

		}

		th++;;

	}


	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->upimg, w / 2 - 150 / 2, 5, 1.0);
	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->downimg, w / 2 - 150 / 2, h - 42 - 5 - 82, 1.0);

	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 10, h - 30, w-20, 20,  0x8B, 0x8B, 0x8B);
	
	
	int xxx = (int)(load * (w - 30.0));
	
	if (load < 0.9) {
		mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 15, h - 25, xxx, 10, 0x00, 0xFF, 0x00);
	}
	else {

		if (load > 1.0) xxx = w - 30;

		mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 15, h - 25, xxx, 10, 0xFF, 0x00, 0x00);

	}

	swprintf_s(frametext->text, 100, L"Load: %3.1f%%", (load*100.0));

}





void ObjectWindow::mouseRclick(int mox, int moy) {

	tmpmox = mox;
	tmpmoy = moy;

	int xx = 0;
	int yy = 0;

	int th = starth;

	for (int i = 0; i < bh*2; i++) {

		if (th < mainwindow->MyAnimationWindow->imagearr.size()) {

			if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {
			
				if (hit(mox, moy, xx, yy)) {

					mainwindow->MyImageChanger->source = OBJECTWINSENDER;
				
					selected = th;// findId(th);

					mainwindow->MyAnimationWindow->selected = th;

					showmenu(mox, moy);

					
				
					return;

				}

			}

			if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {

				xx++;

				if (xx > 1) {

					xx = 0;

					yy++;

				}
			}

			th++;

		}

	}

}

void ObjectWindow::mouseRup(int mox, int moy) {


	

}

void ObjectWindow::mouseclick(int mox, int moy) {
		
	

	int xx = 0;
	int yy = 0;

	int th = starth;

	for (int i = 0; i < bh*2; i++) {

		if (th < mainwindow->MyAnimationWindow->imagearr.size()) {

			if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {
				if (hit(mox, moy, xx, yy)) {
					
					if (mainwindow->MyAnimationWindow->cross) {

						mainwindow->MyAnimationWindow->bind(selected , th);

						mainwindow->MyAnimationWindow->cross = false;
					
					} else {

						mainwindow->MyAnimationWindow->selected = th;// findId(th);

					}
					return;

				}

			}

	


			if (mainwindow->MyAnimationWindow->currscene == mainwindow->MyAnimationWindow->imagearr[th]->scene) {

				xx++;
				if (xx > 1) {

					xx = 0;

					yy++;

				}

			}

			th++;

		}

	}

	mox -= x;
	moy -= y;

	if ((mox > (w / 2 - 150 / 2)) && (moy > (5)) && (mox < (w / 2 + 150 / 2)) && (moy < (5 + 42))) {

		if (starth > 0) starth = starth - 2;

	}



	if ((mox > (w / 2 - 150 / 2)) && (moy > (h - 42 - 5)) && (mox < (w / 2 + 150 / 2)) && (moy < (h - 42 - 5 + 42))) {

		if ((starth + bh * 2) < mainwindow->MyAnimationWindow->imagearr.size())
			starth = starth + 2;

	}

	


}




int ObjectWindow::findId(int i) {

	for (int j = 0; j < mainwindow->MyAnimationWindow->imagearr.size(); j++) {

		if (mainwindow->MyAnimationWindow->imagearr[j]->id == i)
			return j;

	}

	return -1;

}



bool ObjectWindow::hit(int mox, int moy , int xx, int yy) {

	return ((mox > (x + 10 + xx * 100)) && (moy > (y + 10 + yy * 100 +42)) && (mox < (x + 10 + xx * 100 + 80)) && (moy < (y + 10 + yy * 100 + 80 + 42)));

}


void ObjectWindow::showImageChanger() {


	mainwindow->imagechangerup = true;

	mainwindow->MyImageChanger->resize(tmpmox, tmpmoy, (int)mainwindow->MyDxstuff->arr.size());

}


void ObjectWindow::changeImage(int im) {

	mainwindow->MyAnimationWindow->imagearr[selected]->data = mainwindow->MyDxstuff->arr[im]->data;
	mainwindow->MyAnimationWindow->imagearr[selected]->w = mainwindow->MyDxstuff->arr[im]->w;
	mainwindow->MyAnimationWindow->imagearr[selected]->h = mainwindow->MyDxstuff->arr[im]->h;
	mainwindow->MyAnimationWindow->imagearr[selected]->imagelink = im;

	mainwindow->MyAnimationWindow->setCue();

}




void ObjectWindow::showmenu(int mmx, int mmy) {


	mainwindow->MyMenu->texter.clear();


	wcsncpy_s(td[0].text, 20, wc0, wcslen(wc0));
	wcsncpy_s(td[1].text, 20, wc1, wcslen(wc1));
	wcsncpy_s(td[2].text, 20, wc2, wcslen(wc2));
	wcsncpy_s(td[3].text, 20, wc3, wcslen(wc3));
	wcsncpy_s(td[4].text, 20, wc4, wcslen(wc4));
	wcsncpy_s(td[5].text, 20, wc5, wcslen(wc5));
	wcsncpy_s(td[6].text, 20, wc6, wcslen(wc6));
	wcsncpy_s(td[7].text, 20, wc7, wcslen(wc7));

	td[0].sender = OBJECTWINSENDER;
	td[1].sender = OBJECTWINSENDER;
	td[2].sender = OBJECTWINSENDER;
	td[3].sender = OBJECTWINSENDER,
	td[4].sender = OBJECTWINSENDER;
	td[5].sender = OBJECTWINSENDER,
	td[6].sender = OBJECTWINSENDER;
	td[7].sender = OBJECTWINSENDER;

	mainwindow->MyMenu->addtext(&td[0]);
	mainwindow->MyMenu->addtext(&td[1]);
	mainwindow->MyMenu->addtext(&td[2]);
	mainwindow->MyMenu->addtext(&td[3]);
	mainwindow->MyMenu->addtext(&td[4]);
	mainwindow->MyMenu->addtext(&td[5]);
	mainwindow->MyMenu->addtext(&td[6]);
	mainwindow->MyMenu->addtext(&td[7]);


	mainwindow->menuup = true;

	mainwindow->MyMenu->setsize();

	if (mmx > (int)(mainwindow->MyDxstuff->size.width - mainwindow->MyMenu->w)) {

		mainwindow->MyMenu->x = mainwindow->MyDxstuff->size.width - mainwindow->MyMenu->w;

	}
	else {

		mainwindow->MyMenu->x = mmx;

	}

	if (mmy > (int)(mainwindow->MyDxstuff->size.height - mainwindow->MyMenu->h)) {

		mainwindow->MyMenu->y = mainwindow->MyDxstuff->size.height - mainwindow->MyMenu->h;

	}
	else {

		mainwindow->MyMenu->y = mmy;

	}

		mainwindow->MyMenu->setsize();
		
}

