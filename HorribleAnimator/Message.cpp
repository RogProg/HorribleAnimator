#include "framework.h"
#include "Message.h"


Message::Message(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {

	

}

void Message::paint() {


	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 200, 200, 200);

	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h, 0, 0, w - 1, h - 1, 0, 0, 0);

	mainwindow->MyDxstuff->drawbitmap(lmem, w, h, -1, mainwindow->MyDxstuff->okimg, w/2 - 100/2, h - 60, 1.0);

}


void Message::showMessage(WCHAR* txt) {

	x = mainwindow->MyDxstuff->size.width / 2 - 300 / 2;
	y = mainwindow->MyDxstuff->size.height / 2 - 300 / 2;

	mainwindow->messageup = true;

	setText(txt);


}


void Message::setText(WCHAR* txt) {

	textdata* td = (textdata*)malloc(sizeof(textdata));

	
	wcsncpy_s(td[0].text, 1000, txt, wcslen(txt));
	
	td->x = x + 10;
	td->y = y + 10;

	addtext(td);
	
}


void Message::mouseclick(int mox, int moy) {

}

void Message::mouseup(int mox, int moy) {

	mox = mox - x;
	moy = moy - y;

	if ((mox > (w / 2 - 100 / 2)) && (moy > (h - 60)) && (mox < (w / 2 + 100 / 2)) && (moy < (h - 10))) {

		mainwindow->messageup = false;

	}


}