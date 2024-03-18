#include "framework.h"
#include "MainWindow.h"


MainWindow::MainWindow(HWND _hWnd) {

	hWnd = _hWnd;
		
	
	MyDxstuff = new Dxstuff(hWnd,this);

	MyBrowser = new Browser(this, 0, 0, BROWSERWIDTH, MyDxstuff->size.height);

	MyAnimationWindow = new AnimationWindow(this, BROWSERWIDTH,0, MyDxstuff->size.width- BROWSERWIDTH - OBJECTWINDOWWIDTH, MyDxstuff->size.height- TIMERBARHEIGHT);

	MyTimeBar = new TimeBar(this, BROWSERWIDTH, MyDxstuff->size.height- TIMERBARHEIGHT, MyDxstuff->size.width - BROWSERWIDTH- OBJECTWINDOWWIDTH, TIMERBARHEIGHT);
	
	MyObjectWindow = new ObjectWindow(this, MyDxstuff->size.width - OBJECTWINDOWWIDTH, 0 , OBJECTWINDOWWIDTH, MyDxstuff->size.height);

	MyFloater = new Floater(this, 0, 0, 80, 80);

	MyMenu = new Menu(this, 0, 0, 200, 200);

	MyImageChanger = new ImageChanger(this, 0, 0, 500, 500);

	MyMessage = new Message(this, 0, 0, 300, 300);

	menuup = false;

	MySoundStuff = new SoundStuff(this);

	MyUndoClass = new UndoClass(this);


//	MyMpeg = new Mpeg(this);

}


void MainWindow::resize() {

	MyDxstuff->createDevices();

	MyBrowser->resize(0, 0, BROWSERWIDTH, MyDxstuff->size.height);

	MyAnimationWindow->resize(BROWSERWIDTH, 0, MyDxstuff->size.width - BROWSERWIDTH - OBJECTWINDOWWIDTH, MyDxstuff->size.height - TIMERBARHEIGHT);

	MyTimeBar->resize(BROWSERWIDTH, MyDxstuff->size.height - TIMERBARHEIGHT, MyDxstuff->size.width - BROWSERWIDTH - OBJECTWINDOWWIDTH, TIMERBARHEIGHT);

	MyObjectWindow->resize(MyDxstuff->size.width - OBJECTWINDOWWIDTH, 0, OBJECTWINDOWWIDTH, MyDxstuff->size.height);

	MyFloater = new Floater(this, 0, 0, 80, 80);

	MyMenu = new Menu(this, 0, 0, 200, 200);

	MyImageChanger->resize(0, 0 , 0);

	MyMessage->resize(0, 0, 300, 300);
	
}

void MainWindow::paint() {


	MyAnimationWindow->paint();
	MyBrowser->paint();
	MyTimeBar->paint();
	MyObjectWindow->paint();

	if (MyBrowser->selected != -1) {

		MyFloater->x =  MyBrowser->sx - 40;
		MyFloater->y =  MyBrowser->sy - 40;

		MyFloater->paint((imagedata*)MyDxstuff->arr[MyBrowser->selected]);
	}

	if (menuup) {
	
		MyMenu->paint();

	}

	if (imagechangerup) {

		MyImageChanger->paint();
	}

	if (messageup) {

		MyMessage->paint();

	}

	t += 0.1;

}

void MainWindow::drawit() {


	MyDxstuff->m_pRenderTarget->BeginDraw();

	MyAnimationWindow->drawit();
	MyBrowser->drawit();
	MyTimeBar->drawit();
	MyObjectWindow->drawit();

	if (MyBrowser->selected != -1) {
		MyFloater->drawit();
	}

	if (menuup) {

		MyMenu->drawit();

	}

	if (imagechangerup) {

		MyImageChanger->drawit();
	}

	if (messageup) {

		MyMessage->drawit();
	}


	MyDxstuff->m_pRenderTarget->EndDraw();

	t += 0.1;

}


void MainWindow::mouseclick(int mox, int moy) {



	if (messageup) {

		if (MyMessage->isIn(mox, moy)) MyMessage->mouseclick(mox, moy);

		return;

	}

	if (imagechangerup) {

		MyImageChanger->mouseclick(mox, moy);

		return;

	}

	if (MyBrowser->isIn(mox, moy)) MyBrowser->mouseclick(mox, moy);
	if (MyAnimationWindow->isIn(mox, moy)) MyAnimationWindow->mouseclick(mox, moy);
	if (MyTimeBar->isIn(mox, moy)) MyTimeBar->mouseclick(mox, moy);
	if (MyObjectWindow->isIn(mox, moy)) MyObjectWindow->mouseclick(mox, moy);

	
	
}

void MainWindow::mouseRclick(int mox, int moy) {


	if (MyAnimationWindow->isIn(mox, moy)) MyAnimationWindow->mouseRclick(mox, moy);
	if (MyObjectWindow->isIn(mox,moy))  MyObjectWindow->mouseRclick(mox, moy);
	if (MyBrowser->isIn(mox, moy))  MyBrowser->mouseRclick(mox, moy);

}

void MainWindow::mouseup(int mox, int moy) {

	if (messageup) {
		MyMessage->mouseup(mox, moy);
		
		return;
	}


	if (imagechangerup) {
		MyImageChanger->mouseup(mox, moy);
		return;
	}


	MyBrowser->mouseup(mox, moy);
	if (MyAnimationWindow->isIn(mox, moy)) MyAnimationWindow->mouseup(mox, moy);
	MyTimeBar->mouseup(mox, moy);

}

void MainWindow::mouseRup(int mox, int moy) {

	
	if (menuup) 
		MyMenu->mouseRup(mox, moy);
	
	menuup = false;

	if (MyAnimationWindow->isIn(mox, moy)) MyAnimationWindow->mouseRup(mox, moy);

	MyObjectWindow->mouseRup(mox, moy);
	

}

void MainWindow::mousemove(int mox, int moy) {

	if (messageup) return;

	MyBrowser->mousemove(mox, moy);
	MyAnimationWindow->mousemove(mox, moy);
	MyTimeBar->mousemove(mox, moy);


	if (menuup)
		MyMenu->mousemove(mox, moy);



}


