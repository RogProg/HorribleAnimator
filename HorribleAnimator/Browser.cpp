#include "framework.h"
#include "Browser.h"


Browser::Browser(MainWindow* _mainwindow , int _x,  int _y, int _w , int _h) : BaseWindow( _mainwindow, _x, _y, _w, _h) {

	selected = -1;

	find_number();

	paintnow = true;

};


void Browser::resize(int _x, int _y, int _w, int _h) {

	BaseWindow::resize(_x, _y, _w, _h);

	find_number();

	paintnow = true;

}

void Browser::find_number() {

	bh = (h - 42 * 2 - 10 - 82) / 100;

}

void Browser::mouseclick(int mox, int moy) {

	int xx = 0;
	int yy = 0;

	int th = starth;

	for (int i = 0; i < bh*2; i++) {


		if ((mox > (10 + xx * 100)) && (moy > (42 + 10 + yy * 100)) && (mox < (10 + xx * 100 + 80)) && (moy < (42 + 10 + yy * 100 + 80))){
				
			if (th < mainwindow->MyDxstuff->arr.size())
			
				selected = th;


			sx = mox - x;// 10 + xx * 100;
			sy = moy - y;// 10 + yy * 100;
					
		}

		th++;

		xx++;
		if (xx > 1) {

			xx = 0;

			yy++;

		}

	}
		
	if ((mox >= w / 2 - 150 / 2) && (moy > 5) && (mox < w / 2 + 150 / 2) && (moy < (5 + 42))) {

		if (starth > 0) starth = starth - 2;

		paintnow = true;

	}

	if ((mox >= w / 2 - 150 / 2) && (moy > (h - 42 - 5 - 82)) && (mox < w / 2 + 150 / 2) && (moy < (h - 42 - 5 - 82 + 42))) {

		

		if ((starth + bh*2) < mainwindow->MyDxstuff->arr.size())
			starth = starth + 2;

		paintnow = true;

	}



	if ((mox >= 96) && (moy > (h - 82)) && (mox < 137) && (moy < h)) {

		mainwindow->MyTimeBar->frame_left();

	}



	if ((mox >= 149) && (moy > (h - 82)) && (mox < 188) && (moy < h)) {

		mainwindow->MyTimeBar->frame_right();
		
	}

	if ((mox >= 19) && (moy > (h - 82)) && (mox < 51) && (moy < h)) {

		if (mainwindow->MyTimeBar->endpoint == 0) {

			MessageBox(mainwindow->hWnd, L"Set endpoint or load Wav file!", L"Warning!", MB_OK);

			return;

		}


		mainwindow->MyAnimationWindow->play = true;

		mainwindow->MySoundStuff->soundpos = 2 * 44100 / 25 * mainwindow->MyTimeBar->slider;
		
	}


	if ((mox >= 61) && (moy > (h - 82)) && (mox < 84) && (moy < h)) {


		mainwindow->MyAnimationWindow->play = false;

		mainwindow->MySoundStuff->stop();
	}



}


void Browser::mouseup(int mox, int moy) {

	int tmpx = mox - x;
	int tmpy = moy - y;

	if ((selected != -1) && mainwindow->MyAnimationWindow->isIn(tmpx,tmpy)) {

		imagedata* tmp = (imagedata*)mainwindow->MyDxstuff->arr[selected];

		imagedata* id = new imagedata;

		id->id = (int)mainwindow->MyAnimationWindow->imagearr.size();

		id->time = mainwindow->MyAnimationWindow->findPrevScene(mainwindow->MyTimeBar->slider);

		id->data = tmp->data;

		id->scene = mainwindow->MyAnimationWindow->MyDataObject->getScene(mainwindow->MyTimeBar->slider);


		id->ch = tmp->ch;
		id->w = tmp->w;
		id->h = tmp->h;

		id->tmpw = id->w;

		id->sw = id->w;
		id->sh = id->h;

		id->rotposx = 0;
		id->rotposy = 0;

		id->ofsx = 0;
		id->ofsy = 0;

		id->angle = 0;

		id->size = 1.0;

		id->x = (mox - mainwindow->MyAnimationWindow->x) / mainwindow->MyAnimationWindow->ratio;
		id->y = (moy - mainwindow->MyAnimationWindow->y) / mainwindow->MyAnimationWindow->ratio;

		id->aspect = tmp->aspect;

		id->imagelink = tmp->id;

		int cuenr2 = -1;
			
		int ps = mainwindow->MyAnimationWindow->findPrevScene(mainwindow->MyTimeBar->slider);

		if (ps != mainwindow->MyTimeBar->slider) {

			imagedata* invcue = new imagedata;

			memcpy(invcue, id, sizeof(imagedata));

			invcue->visible = true;

			invcue->time = mainwindow->MyTimeBar->slider;

			cuenr2 = mainwindow->MyAnimationWindow->MyDataObject->storeCuepoint(invcue, invcue->time, false);

			id->visible = false;
			
		} else {

			id->visible = true;

		}


		mainwindow->MyAnimationWindow->addimage(id);
		mainwindow->MyObjectWindow->addimage(id);

		mainwindow->MyAnimationWindow->selected = (int)mainwindow->MyAnimationWindow->imagearr.size () - 1;
				
		int cuenr1  = mainwindow->MyAnimationWindow->MyDataObject->storeCuepoint(id, ps , false);

		mainwindow->MyUndoClass->store_newimage((int)mainwindow->MyAnimationWindow->imagearr.size() - 1, cuenr1,cuenr2);

		mainwindow->MyAnimationWindow->imagearr[mainwindow->MyAnimationWindow->selected]->visible = true;

		//mainwindow->MyAnimationWindow->MyDataObject->update(mainwindow->MyTimeBar->slider);


	} else {

		if ((selected != -1) && (mainwindow->MyAnimationWindow->selected != -1)) {

			mainwindow->MyAnimationWindow->menuselect = mainwindow->MyAnimationWindow->selected;

			//mainwindow->MyUndoClass->store_change_image(mainwindow->MyAnimationWindow->imagearr[mainwindow->MyAnimationWindow->selected]->imagelink);

			
 			mainwindow->MyAnimationWindow->changeImage(selected);

			mainwindow->MyAnimationWindow->MyDataObject->update(mainwindow->MyTimeBar->slider);
		}


	}

	selected = -1;

}

void Browser::mousemove(int mox, int moy) {

	sx = mox - x;
	sy = moy - y;

}



void Browser::mouseRclick(int mox, int moy) {

	

	int xx = 0;
	int yy = 0;

	int th = starth;

	for (int i = 0; i < bh * 2; i++) {

		if (th < mainwindow->MyDxstuff->arr.size()) {

			

			if (hit(mox, moy, xx, yy)) {
						
				loadsel = th;

				showmenu(mox, moy);


				return;

			}

		
			xx++;
			
			if (xx > 1) {

				xx = 0;

				yy++;

			}
			
			th++;

		}

	}

}

bool Browser::hit(int mox, int moy, int xx, int yy) {

	return ((mox > (x + 10 + xx * 100)) && (moy > (y + 10 + yy * 100 + 42)) && (mox < (x + 10 + xx * 100 + 80)) && (moy < (y + 10 + yy * 100 + 80 + 42)));

}

void Browser::showmenu(int mmx, int mmy) {


	mainwindow->MyMenu->texter.clear();


	wcsncpy_s(td[0].text, 20, wc0, wcslen(wc0));
	wcsncpy_s(td[1].text, 20, wc1, wcslen(wc1));



	td[0].sender = BROWSERSENDER;
	td[1].sender = BROWSERSENDER;

	mainwindow->MyMenu->addtext(&td[0]);
	mainwindow->MyMenu->addtext(&td[1]);

	mainwindow->menuup = true;

	mainwindow->MyMenu->x = mmx;

	mainwindow->MyMenu->y = mmy;


	mainwindow->MyMenu->setsize();

	
	if ((int)mmy > (int)(mainwindow->MyDxstuff->size.height - mainwindow->MyMenu->h)) {

		mainwindow->MyMenu->y = mainwindow->MyDxstuff->size.height - mainwindow->MyMenu->h;

	}
	else {

		mainwindow->MyMenu->y = mmy;

	}

	mainwindow->MyMenu->setsize();

}



void Browser::paint() {

	if (!paintnow) return;

	paintnow = false;

	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem,w,0, 0, w, h, 100, 100, 100);
	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 0, 0, w - 1, h - 1, 20, 20, 20);


	int th = starth;

	int xx = 0;
	int yy = 0;

	for (int i = 0; i < bh*2; i++) {


		if (th < mainwindow->MyDxstuff->arr.size()) {

			mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 10 + xx * 100, 42 + 10 + yy * 100, 80, 80, 180, 180, 180);

			mainwindow->MyDxstuff->drawbitmapscaleQuick(lmem, w, h, i, (imagedata*)mainwindow->MyDxstuff->arr[th], 10 + xx * 100, 42 + 10 + yy * 100, 1.0);

			mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 10 + xx * 100, 42 + 10 + yy * 100, 10 + xx * 100 + 80, 42 + 10 + yy * 100 + 80, 0, 0, 0);

		}

		th++;

		xx++;
		if (xx > 1) {

			xx = 0;

			yy++;

		}

	}
	

	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->upimg, w / 2 - 150 / 2, 5, 1.0);
	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->downimg, w / 2 - 150 / 2, h - 42 - 5 - 82, 1.0);

	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->controlimg, 0, h - 82, 1.0);

};


void Browser::loadfile(int indx) {


	OPENFILENAMEW ofn;
	WCHAR szFileName[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
	ofn.hwndOwner = mainwindow->hWnd;
	ofn.lpstrFilter = L"Images\0*.bmp\0\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = L"txt";
	

	if (GetOpenFileNameW(&ofn))
	{


		imagedata* id = mainwindow->MyDxstuff->MyBMPLoader->loadfile(ofn.lpstrFile);

		if (id == 0) {

			MessageBoxW(mainwindow->hWnd, L"Unable to load BMP", L"Error", MB_OK);

			return;

		}
		


		id->sw = 80;
		id->sh = 80;

		id->aspect = (double)id->w / id->h;

		mainwindow->MyDxstuff->arr[indx] = id;

		mainwindow->MyBrowser->paintnow = true;

		mainwindow->MyAnimationWindow->MyDataObject->update(mainwindow->MyTimeBar->slider);



	}



}