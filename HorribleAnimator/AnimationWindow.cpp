#include "framework.h"
#include "AnimationWindow.h"


AnimationWindow::AnimationWindow(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {


	indexbuffer = (int*)malloc(w * h * sizeof(int));
	indexbufferbase = (int*)malloc(w * h * sizeof(int));

	resetbuffer();

	crossCursor = LoadCursor(NULL, IDC_CROSS);

	MyRotater = new Rotater(_w, _h ,this);

	MyDataObject = new DataObject(mainwindow);

	background.clear();

	newScene(0);

	setratio();

}


void AnimationWindow::resize(int _x, int _y, int _w, int _h) {

	BaseWindow::resize(_x, _y, _w, _h);

	free(indexbufferbase);
	free(indexbuffer);

	indexbufferbase = (int*)malloc(w * h * sizeof(int));
	indexbuffer = (int*)malloc(w * h * sizeof(int));

	for (int i = 0; i < w * h; i++)
		indexbufferbase[i] = -1;

	resetbuffer();

	if (MyRotater == NULL) delete(MyRotater);
	
	MyRotater = new Rotater(_w, _h, this);

	setratio();

	update_backgrounds();



}

void AnimationWindow::setratio() {

	double tmpratio = (double)w / h;

	if (tmpratio < HDRATIO) {

		vieww = w;
		viewh = (int)floor((double)w / HDRATIO);

	}
	else {

		vieww = (int)floor((double)h * HDRATIO);
		viewh = h;

	}

	boxx1 = (int)ceil((double)(w - vieww) / 2);
	boxy1 = (int)ceil((double)(h - viewh) / 2);
	boxx2 = (int)floor(vieww + (double)(w - vieww) / 2);
	boxy2 = (int)floor(viewh + (double)(h - viewh) / 2);


	ratio = ((double) vieww / HDW);


}


void AnimationWindow::newScene(int scenetime) {

	
 	
	if ((background.size() > 0) && (background[background.size() - 1]->time >= mainwindow->MyTimeBar->slider)) {

		MessageBoxW(mainwindow->hWnd, L"Cannot insert scene!", L"Error", MB_OK);

		return;

	}
	/*
	for (int i = 0; i < imagearr.size(); i++) {

		if (imagearr[i]->scene == currscene) MyDataObject->storeCuepoint(imagearr[i],scenetime,true);

	}
	*/

	imagedata* news = new imagedata;

	news->data = NULL;

	news->scene = (int)background.size();

	news->time = scenetime;

	news->id = -1;

	background.push_back(news);

	currscene = (int)background.size() - 1;

}


void AnimationWindow::selectBackground() {


	mainwindow->MyImageChanger->source = NEWBACKGROUNDSENDER;


	mainwindow->imagechangerup = true;

	
	mainwindow->MyImageChanger->resize(100,0, (int)mainwindow->MyDxstuff->arr.size());


}

void AnimationWindow::changeBackground(int im) {

	currscene = MyDataObject->getScene(mainwindow->MyTimeBar->slider);
	
	
	imagedata* tmpim = new imagedata;

	memcpy(tmpim, mainwindow->MyDxstuff->arr[im], sizeof(imagedata));

	tmpim->sw = vieww;
	tmpim->sh = viewh;

	background[currscene]->id = im;

	if (background[currscene]->data != NULL)
		free(background[currscene]->data);

	background[currscene]->data = (byte*)malloc(w * h * 4);

	mainwindow->MyDxstuff->drawbitmapscaleQuick(background[currscene]->data, w, h, -1, tmpim, boxx1, boxy1, 1.0);

		
}




void AnimationWindow::gotoPrevCue() {

	if (selected != -1) {

		int foundtime = MyDataObject->findPrevCue(selected,mainwindow->MyTimeBar->slider);

		if (foundtime != -1) {

			if (mainwindow->MyTimeBar->is_in_slider(foundtime)) {

				mainwindow->MyTimeBar->sliderx = foundtime - mainwindow->MyTimeBar->offset;

			}
			else {

				mainwindow->MyTimeBar->sliderx = 0;

				mainwindow->MyTimeBar->offset = foundtime;

			}


		}

		MyDataObject->update(foundtime);

	}
}


void AnimationWindow::gotoNextCue() {

	if (selected != -1) {

		int foundtime = MyDataObject->findNextCue(selected, mainwindow->MyTimeBar->slider);

		if (foundtime != -1) {

			if (mainwindow->MyTimeBar->is_in_slider(foundtime)) {

				mainwindow->MyTimeBar->sliderx = foundtime - mainwindow->MyTimeBar->offset;

			}
			else {

				mainwindow->MyTimeBar->sliderx = mainwindow->MyTimeBar->slidermax;

				mainwindow->MyTimeBar->offset = foundtime - mainwindow->MyTimeBar->slidermax;

			}
			

		}
		
		MyDataObject->update(foundtime);
	
	}

}


void AnimationWindow::setCue() {

	if (menuselect != -1) {

		MyDataObject->storeCuepoint(imagearr[menuselect], mainwindow->MyTimeBar->slider,true);

	}

}

void AnimationWindow::paint() {

	if (play) {
				
		MyDataObject->update(mainwindow->MyTimeBar->slider);
	
	}


	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 200, 200, 200);

	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem,w,h,0, 0, w-1, h-1, 0, 0, 0);

	sortarr.clear();

	int tmpselected = -1;

	for (int i = 0; i < imagearr.size(); i++) {

		for (int j = 0; j < imagearr.size(); j++) {
		
			if (imagearr[j]->layer == i) {

				if (selected == j) 			
					tmpselected = (int)sortarr.size();

				sortarr.push_back(imagearr[j]);


			}
		}

	}

	currscene = MyDataObject->getScene(mainwindow->MyTimeBar->slider);
	
	if (background[currscene]->data != NULL)

		memcpy(lmem, background[currscene]->data, w * h * 4);
	

	

	for (int i = 0; i < sortarr.size(); i++) {

		double tint = 1.0;

		if (sortarr[i]->visible) {

			if (tmpselected == i) tint = 0.7;

			if (currscene == sortarr[i]->scene) {

				MyRotater->rotateNscale(lmem, indexbuffer, sortarr[i]->id, sortarr[i], ((imagedata*)sortarr[i])->angle, ((imagedata*)sortarr[i])->size, (int)((imagedata*)sortarr[i])->x + boxx1, (int)((imagedata*)sortarr[i])->y + boxy1, tint, ratio);



				if (i == tmpselected) {

					memcpy(xx, MyRotater->xx, sizeof(double) * 4);
					memcpy(yy, MyRotater->yy, sizeof(double) * 4);

				}

			}

		}

		if ((selected != -1) && (currscene == imagearr[selected]->scene) && (imagearr[selected]->visible)) {

			mainwindow->MyDxstuff->MyGfxTools->drawLine(lmem, w, h, (int)xx[0], (int)yy[0], (int)xx[1], (int)yy[1], 255, 0, 0);
			mainwindow->MyDxstuff->MyGfxTools->drawLine(lmem, w, h, (int)xx[1], (int)yy[1], (int)xx[2], (int)yy[2], 255, 0, 0);
			mainwindow->MyDxstuff->MyGfxTools->drawLine(lmem, w, h, (int)xx[2], (int)yy[2], (int)xx[3], (int)yy[3], 255, 0, 0);
			mainwindow->MyDxstuff->MyGfxTools->drawLine(lmem, w, h, (int)xx[3], (int)yy[3], (int)xx[0], (int)yy[0], 255, 0, 0);



			rpx = (int)((((imagedata*)imagearr[selected])->x + ((imagedata*)imagearr[selected])->rotposx * ((imagedata*)imagearr[selected])->size) * ratio);
			rpy = (int)((((imagedata*)imagearr[selected])->y + ((imagedata*)imagearr[selected])->rotposy * ((imagedata*)imagearr[selected])->size) * ratio);

			mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, rpx - 5, rpy - 5, rpx + 4, rpy + 4, 255, 0, 0);

			rx = (int)xx[2];
			ry = (int)yy[2];

			mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, rx - 5, ry - 5, rx + 4, ry + 4, 0, 255, 0);


			sx = (int)xx[0];
			sy = (int)yy[0];

			mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, sx - 5, sy - 5, sx + 4, sy + 4, 0, 0, 255);

		}

	}

	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, boxx1-1,boxy1-1,boxx2,boxy2, 0, 0, 255);
	
	
}

void AnimationWindow::resetbuffer() {

	memcpy(indexbuffer, indexbufferbase, w * h * 4);

}


void AnimationWindow::bind(int parent, int bindto) {

	 
	if (parent == bindto) {

		MessageBoxW(mainwindow->hWnd, L"Cannot make self child!", L"Warning", MB_OK);

		mousedown = false;

		return;

	}

	imagedata* searchid = imagearr[parent];

	if (searchid->parent == bindto) {
			
		MessageBoxW(mainwindow->hWnd, L"Circular reference!", L"Warning", MB_OK);

		mousedown = false;

		return;
	}

	while (searchid->parent != -1) {

		searchid = imagearr[searchid->parent];

		if (searchid->parent == bindto) {

			MessageBoxW(mainwindow->hWnd, L"Circular reference!", L"Warning", MB_OK);

			mousedown = false;

			return;
		}
	}



	imagearr[bindto]->parent = parent;

	double s = get_size(bindto);

	if (imagearr[bindto]->parent != -1) {

		imagearr[bindto]->ofsx = (imagearr[bindto]->x - imagearr[parent]->x) / s;// imagearr[parent]->size;
		imagearr[bindto]->ofsy = (imagearr[bindto]->y - imagearr[parent]->y) / s;// imagearr[parent]->size;

		imagearr[bindto]->ownsize /= s;// imagearr[parent]->ownsize;

		int rootparent = getRootParent(bindto);
		
		movechild(rootparent, imagearr[rootparent]->x, imagearr[rootparent]->y, imagearr[rootparent]->size);

		
	}
	
	MyDataObject->storeCuepoint(imagearr[bindto], findPrevScene(mainwindow->MyTimeBar->slider),true);

}



void AnimationWindow::mouseclick(int mox, int moy) {

	mousedown = true;

	tmpx = mox - x;
	tmpy = moy - y;


	move = indexbuffer[tmpx + tmpy * w];

	if (cross) {

		bind(selected , indexbuffer[mox - x + (moy - y) * w]);

		cross = false;

		return;

	}

	if ((tmpx > (rx - 5)) && (tmpy > (ry - 5)) && (tmpx < (rx + 4)) && (tmpy < (ry + 4))) {

		rotdrag = true;

		oldrot = ((imagedata*)imagearr[selected])->angle;

		//move = -1;

		return;

	}

	if ((tmpx > (rpx - 5)) && (tmpy > (rpy - 5)) && (tmpx < (rpx + 4)) && (tmpy < (rpy + 4))) {

		rotposdrag = true;

		return;

	}
	


	if ((tmpx > (sx - 5)) && (tmpy > (sy - 5)) && (tmpx < (sx + 4)) && (tmpy < (sy + 4))) {

		sizedrag = true;

		oldsize = ((imagedata*)imagearr[selected])->ownsize;

		return;

	}






	if (indexbuffer[tmpx + tmpy * w] != -1) {

		imagedata* im = imagearr[indexbuffer[tmpx + tmpy * w]];

		oldx = im->x;
		oldy = im->y;
		
		mx = tmpx;
		my = tmpy;

		selected = indexbuffer[tmpx + tmpy * w];

	}

	
	selected = indexbuffer[tmpx + tmpy * w];

	if (selected != -1) {

		ShowCursor(false);

	}
			

}


void AnimationWindow::mouseRclick(int mox, int moy) {

	ictmpx = mox;
	ictmpy = moy;
		

	menuselect = indexbuffer[mox - x + (moy - y) * w];

	selected = indexbuffer[mox - x + (moy - y) * w];

	showmenu(mox, moy, AINIMATIONWINDOWSENDER);


}


void AnimationWindow::showmenu(int mmx, int mmy, int sender) {


	if ((sender == OBJECTWINSENDER) || (menuselect != -1)) {

		mainwindow->MyMenu->texter.clear();

		wcsncpy_s(td[0].text, 20, wc0, wcslen(wc0) + 1);
		wcsncpy_s(td[1].text, 20, wc1, wcslen(wc1) + 1);
		wcsncpy_s(td[2].text, 20, wc2, wcslen(wc2) + 1);
		wcsncpy_s(td[3].text, 20, wc3, wcslen(wc3) + 1);
		wcsncpy_s(td[4].text, 20, wc4, wcslen(wc4) + 1);
		wcsncpy_s(td[5].text, 20, wc5, wcslen(wc5) + 1);

		td[0].sender = sender;
		td[1].sender = sender;
		td[2].sender = sender;
		td[3].sender = sender,
		td[4].sender = sender;
		td[5].sender = sender;

		mainwindow->MyMenu->addtext(&td[0]);
		mainwindow->MyMenu->addtext(&td[1]);
		mainwindow->MyMenu->addtext(&td[2]);
		mainwindow->MyMenu->addtext(&td[3]);
		mainwindow->MyMenu->addtext(&td[4]);
		mainwindow->MyMenu->addtext(&td[5]);

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

}


void AnimationWindow::mouseup(int mox, int moy) {

	mainwindow->menuup = false;

	mousedown = false;

	if ((sizedrag) && (selected != -1)) {

		imagearr[selected]->tmpw = imagearr[selected]->size * imagearr[selected]->w;

	}

	if (drag || sizedrag || rotdrag) {

		menuselect = selected;

		setCue();

	}

	drag = false;

	sizedrag = false;

	rotposdrag = false;

	rotdrag = false;

	ShowCursor(true);

	//selected = -1;

}

void AnimationWindow::mouseRup(int mox, int moy) {


	mainwindow->menuup = false;

}

void AnimationWindow::mousemove(int mox, int moy) {

	if (cross)
		SetCursor(crossCursor);

	if ((rotposdrag) && (selected != -1)) {


		imagearr[selected]->rotposx = (mox - x)/ratio - imagearr[selected]->x;
		imagearr[selected]->rotposy = (moy - y)/ratio - imagearr[selected]->y;

		return;
	}

	if ((rotdrag) && (selected != -1)) {

		int nw = mox - x - tmpx;
		int nh = moy - y - tmpy;

	
		imagearr[selected]->angle = oldrot + (nw - nh) / 500.0;
	

		//int rootparent = getRootParent(selected);

		//movechild(rootparent, imagearr[rootparent]->x, imagearr[rootparent]->y, imagearr[rootparent]->size);
			
		return;
	}


	if ((sizedrag) && (selected != -1)) {

		int nw = mox - x - tmpx;
		int nh = moy - y - tmpy;

		if ((mox - x) < imagearr[selected]->x) nw = -nw;
		if ((moy - y) < imagearr[selected]->y) nh = -nh;

		if (imagearr[selected]->parent != -1) {

			imagearr[selected]->ownsize = oldsize + (nw + nh) / 500.0;

		}
		else {

			imagearr[selected]->size = oldsize + (nw + nh) / 500.0;

			imagearr[selected]->ownsize = imagearr[selected]->size;

		}

		int rootparent = getRootParent(selected);

		movechild(rootparent, imagearr[rootparent]->x, imagearr[rootparent]->y, imagearr[rootparent]->size);

		return;

	}

	if ((move != -1) && mousedown) {

		drag = true;

		imagedata* im = (imagedata*)imagearr[move];


		im->x = oldx - (mx - (mox - x)) / ratio;
		im->y = oldy - (my - (moy - y)) / ratio;
 

		int rootparent = getRootParent(move);
		
		if (imagearr[move]->parent != -1) {

			double s = get_size(move);

			imagearr[move]->ofsx = (imagearr[move]->x - imagearr[imagearr[move]->parent]->x) / s;// imagearr[imagearr[move]->parent]->ownsize;
			imagearr[move]->ofsy = (imagearr[move]->y - imagearr[imagearr[move]->parent]->y) / s;// imagearr[imagearr[move]->parent]->ownsize;

		}
		else {
		
			

		}

		movechild(rootparent, imagearr[rootparent]->x, imagearr[rootparent]->y, imagearr[rootparent]->size);

	}

		
}

void AnimationWindow::movechild(int parent, double px, double py, double size) {

	for (int i = 0; i < imagearr.size(); i++) {

		if (imagearr[i]->parent == parent) {

			imagearr[i]->x = px + imagearr[i]->ofsx*size;
			imagearr[i]->y = py + imagearr[i]->ofsy*size;

			imagearr[i]->size = size * imagearr[i]->ownsize;
			
			movechild(i, imagearr[i]->x, imagearr[i]->y, imagearr[i]->size);

		}

	}

}

double AnimationWindow::get_size(int child) {

	imagedata* id = imagearr[child];

	double s = 1.0;// id->ownsize;

	while (id->parent != -1) {

		id = imagearr[id->parent];

		s *= id->ownsize;
		
	}

	return s;

}

int AnimationWindow::getRootParent(int child) {


	while (imagearr[child]->parent != -1) {

		child = imagearr[child]->parent;

	}

	return child;

}


void AnimationWindow::update_backgrounds() {
	
	for (int t = 0; t < background.size(); t++) {

	  

		if (background[t]->data != NULL) {

			free(background[t]->data);

			background[t]->data = NULL;

		}

		if (background[t]->id != -1) {


			imagedata* tmpim = new imagedata;

			memcpy(tmpim, mainwindow->MyDxstuff->arr[background[t]->id], sizeof(imagedata));

			tmpim->sw = vieww;
			tmpim->sh = viewh;

			background[t]->data = (byte*)malloc(w * h * 4);

			mainwindow->MyDxstuff->drawbitmapscale(background[t]->data, w, h, -1, tmpim, boxx1, boxy1, 1.0);

		}

	}

}

void AnimationWindow::addimage(imagedata* idata) {


	idata->id = (int)imagearr.size();

	idata->sw = idata->w;
	idata->sh = idata->h;

	idata->layer = (int)imagearr.size();

	idata->parent = -1;

	idata->ownsize = idata->size;

	idata->scene = mainwindow->MyAnimationWindow->MyDataObject->getScene(mainwindow->MyTimeBar->slider);

	idata->time = findPrevScene(mainwindow->MyTimeBar->slider);
	
	imagearr.push_back(idata);

	

}


void AnimationWindow::showImageChanger() {

	if (selected != -1) {

		
		mainwindow->MyImageChanger->source = AINIMATIONWINDOWSENDER;

		mainwindow->imagechangerup = true;

		int calcx = ictmpx - mainwindow->MyImageChanger->w / 2;
		int calcy = ictmpy - mainwindow->MyImageChanger->h / 2;


		


		if (calcx < 0) calcx = 0;
		if (calcy < 0) calcy = 0;

		if (calcx > (mainwindow->MyImageChanger->w + calcx)) calcx = -mainwindow->MyImageChanger->w;
		if (calcy > (mainwindow->MyImageChanger->h + calcy)) calcy = -mainwindow->MyImageChanger->h;

		mainwindow->MyImageChanger->resize(calcx, calcy, (int)mainwindow->MyDxstuff->arr.size());

	}

}





void AnimationWindow::changeImage(int im) {

	//imagearr[menuselect]->data = mainwindow->MyDxstuff->arr[im]->data;
	//imagearr[menuselect]->w = mainwindow->MyDxstuff->arr[im]->w;
	//imagearr[menuselect]->h = mainwindow->MyDxstuff->arr[im]->h;
	imagearr[menuselect]->imagelink = im;

	setCue();

}


int AnimationWindow::findPrevScene(int time) {

	bool found = false;

	int starttime = 0;

	for (imagedata* id : background) {

		if ((id->time >= starttime) && (id->time <= time)) {

			starttime = id->time;

			found = true;

		}

	}

	if (!found) {

		MessageBox(mainwindow->hWnd, L"Scene not found!", L"Waring", MB_OK);

		return -1;

	}

	return starttime;

}


int AnimationWindow::findNextScene(int time) {

	bool found = false;

	int endtime = INT_MAX;

	for (imagedata* id : background) {

		if ((id->time < endtime) && (id->time > time)) {

			endtime = id->time;

			found = true;

		}

	}

	if (!found) return -1;

	return endtime;

}



void AnimationWindow::gotoPrevScene() {

	int foundtime = findPrevScene(mainwindow->MyTimeBar->slider - 1);

	if (foundtime != -1) {

		if (mainwindow->MyTimeBar->is_in_slider(foundtime)) {

			mainwindow->MyTimeBar->sliderx = foundtime - mainwindow->MyTimeBar->offset;

		}
		else {

			mainwindow->MyTimeBar->sliderx = 0;

			mainwindow->MyTimeBar->offset = foundtime;

		}


		MyDataObject->update(foundtime);

	}
}


void AnimationWindow::gotoNextScene() {


		int foundtime = findNextScene(mainwindow->MyTimeBar->slider + 1);

		if (foundtime != -1) {

			if (mainwindow->MyTimeBar->is_in_slider(foundtime)) {

				mainwindow->MyTimeBar->sliderx = foundtime - mainwindow->MyTimeBar->offset;

			}
			else {

				mainwindow->MyTimeBar->sliderx = mainwindow->MyTimeBar->slidermax;

				mainwindow->MyTimeBar->offset = foundtime - mainwindow->MyTimeBar->slidermax;

			}



			MyDataObject->update(foundtime);

		}
}


int AnimationWindow::findCue(int sel,int time) {

	for ( int i = 0; i < MyDataObject->cues.size(); i++) {
		
		if ((MyDataObject->cues[i]->id == sel) && (MyDataObject->cues[i]->time == time))
			return i;

	}

	return -1;

}


void AnimationWindow::move_cue_left() {

	int cueid = findCue(selected, mainwindow->MyTimeBar->slider);

	if ((cueid != -1) && (MyDataObject->findPrevCue(selected, mainwindow->MyTimeBar->slider) != (mainwindow->MyTimeBar->slider - 1))) {

			MyDataObject->cues[cueid]->time--;

			mainwindow->MyTimeBar->frame_left();
					
	}

}

void  AnimationWindow::move_cue_right() {

	int cueid = findCue(selected, mainwindow->MyTimeBar->slider);

	if ((cueid != -1) && (MyDataObject->findNextCue(selected,mainwindow->MyTimeBar->slider) != (mainwindow->MyTimeBar->slider + 1))) {

		MyDataObject->cues[cueid]->time++;

		mainwindow->MyTimeBar->frame_right();

	}

}

void  AnimationWindow::change_visible() {

	imagedata* invdata = new imagedata;

	memcpy(invdata, imagearr[menuselect], sizeof(imagedata));

	invdata->visible = !invdata->visible;

	invdata->time = mainwindow->MyTimeBar->slider;

	MyDataObject->storeCuepoint(invdata, invdata->time, false);

	MyDataObject->update(invdata->time);

}

bool AnimationWindow::is_active() {

	return (drag || sizedrag || rotdrag);

}

