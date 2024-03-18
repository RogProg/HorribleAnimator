#include "framework.h"
#include "TimeBar.h"


TimeBar::TimeBar(MainWindow* _mainwindow , int _x,  int _y, int _w , int _h) : BaseWindow( _mainwindow, _x, _y, _w, _h) {
	
	
	mousedown = false;

	grab = false;

	slider = 0;

	frametext = (textdata*)malloc(sizeof(textdata));

	frametext->x = x + w - 150;
	frametext->y = y + 20;

	addtext(frametext);

	swprintf_s(frametext->text, 100, L"Frame: %i", slider);

	slidermax = w - SLIDEREND - SLIDERBEGIN;

	offset = 0;

	nrl = (w - SLIDERBEGIN - SLIDEREND) / 10;

	

}

void TimeBar::resize(int _x, int _y, int _w, int _h) {

	BaseWindow::resize(_x, _y, _w, _h);

	frametext->x = x + w - 150;
	frametext->y = y + 38;


	slidermax = w - SLIDEREND - SLIDERBEGIN;

	nrl = (w - SLIDERBEGIN - SLIDEREND) / 10;

	

}

void TimeBar::set_slider(int s) {

	if (((s + offset) > SLIDERBEGIN) && ((s + offset) < (w - SLIDERBEGIN - SLIDEREND))) {

		sliderx = s - offset;

	}

}

void TimeBar::paint() {

	if (grab && (tmpx < mainwindow->MyBrowser->w)) {

		if (offset < 5) {

			offset = 0;

		}
		else {

			offset -= 15;

		}

	}

	if (grab && (tmpx > (mainwindow->MyBrowser->w + w - SLIDEREND - SLIDERBEGIN/2))) {

		offset += 15;

	}

	if (mainwindow->MyAnimationWindow->play) {

		if (slider < endpoint) {

			if (sliderx < (w - SLIDEREND - SLIDERBEGIN)) {

				sliderx++;
				slider = sliderx + offset;

			}
			else {

				offset++;

				slider = sliderx + offset;

			}

		}
		else {

			mainwindow->MySoundStuff->stop();

		}
		
	} else {

		slider = sliderx + offset;

	}


	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem,w,0, 0, w, h, 100, 100, 100);
	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w,h, 0, 0, w - 1, h - 1, 20, 20, 20);
		
	mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w,h, SLIDERBEGIN, h/2 - 10, w - SLIDEREND, h/2 + 10, 20, 20, 20);


	
	
	for (int i = 1; i <= 10; i++) {

		mainwindow->MyDxstuff->MyGfxTools->drawVLine(lmem, w, h, i * nrl + SLIDERBEGIN - offset % nrl, h / 2 - SLIDERHEIGTH / 2, h / 2 + SLIDERHEIGTH / 2, 0, 0, 0);

	}
	

	for (int i = 0; i < mainwindow->MyAnimationWindow->MyDataObject->cues.size(); i++) {

		if (mainwindow->MyAnimationWindow->MyDataObject->cues[i]->id == mainwindow->MyAnimationWindow->selected) {

			int tmpt = mainwindow->MyAnimationWindow->MyDataObject->cues[i]->time - offset + SLIDERBEGIN;

			if ((tmpt >= SLIDERBEGIN) && (tmpt < (w - SLIDEREND - SLIDERBEGIN))) {

				mainwindow->MyDxstuff->MyGfxTools->drawVLine(lmem, w, h, tmpt, h / 2 - SLIDERHEIGTH / 2 - 3, h / 2 + SLIDERHEIGTH / 2 + 3, 255, 0, 0);

			}

		}

	}
	
	for (int i = 0; i < mainwindow->MyAnimationWindow->background.size(); i++) {

		int tmpt = mainwindow->MyAnimationWindow->background[i]->time - offset  + SLIDERBEGIN;

		if ((tmpt >= SLIDERBEGIN) && (tmpt < (w - SLIDEREND - SLIDERBEGIN))) {

			mainwindow->MyDxstuff->MyGfxTools->drawVLine(lmem, w, h, tmpt, h / 2 - SLIDERHEIGTH / 2-3, h / 2 + SLIDERHEIGTH / 2+3, 0, 0, 255);

		}

	}
	

	


	if (endpoint != 0) {

		int tmpt = endpoint - offset + SLIDERBEGIN;

		if ((tmpt >= SLIDERBEGIN) && (tmpt < (w - SLIDEREND - SLIDERBEGIN))) {

			mainwindow->MyDxstuff->MyGfxTools->drawVLine(lmem, w, h, tmpt, h / 2 - SLIDERHEIGTH / 2 - 3, h / 2 + SLIDERHEIGTH / 2 + 3, 0, 255, 0);

		}

	}
	
	
	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem,w,sliderx+SLIDERBEGIN - SLIDERWIDTH/2, h/2-SLIDERHEIGTH/2, SLIDERWIDTH, SLIDERHEIGTH, 40, 40, 40);

	swprintf_s(frametext->text, 100, L"Frame: %i", slider);

}

void TimeBar::drawit() {

	BaseWindow::drawit();

	

	int ofsx = mainwindow->MyBrowser->w + SLIDERBEGIN;
	int ofsy = mainwindow->MyAnimationWindow->h;

	int i = 0;

	if ((offset % nrl) == 0) {
		WCHAR* text = (WCHAR*)malloc(10);

		swprintf_s(text, 10, L"%d", i * nrl + offset);

		dxstuff->m_pRenderTarget->DrawText(
			text,
			(int)wcslen(text),
			dxstuff->m_pTextFormatTime,
			D2D1::RectF((float)(i * nrl + (int)ofsx),(float)(10 + (int)ofsy), (float)mainwindow->MyDxstuff->size.width, (float)mainwindow->MyDxstuff->size.height),
			dxstuff->m_pD2DBrush
		);

	}



	for (int i = 1; i <= 10; i++) {

		WCHAR* text = (WCHAR*)malloc(10);

		swprintf_s(text, 10, L"%d", ( i + offset / nrl) * nrl  );

		dxstuff->m_pRenderTarget->DrawText(
			text,
			(int)wcslen(text),
			dxstuff->m_pTextFormatTime,
			D2D1::RectF((float)(i*nrl+ofsx - offset % nrl), (float)(10+ofsy), (float)mainwindow->MyDxstuff->size.width, (float)mainwindow->MyDxstuff->size.height),
			dxstuff->m_pD2DBrush
		);

	}

}



void TimeBar::mouseclick(int mox, int moy) {

	mousedown = true;



	if ((mox > (x + sliderx + SLIDERBEGIN - SLIDERWIDTH/2)) && (moy > (y + (h - SLIDERHEIGTH) / 2)) && (mox < (x + sliderx + SLIDERBEGIN + SLIDERWIDTH/2)) && (moy < ((y + (h + SLIDERHEIGTH) / 2 + 40)))) {

		grab = true;

		mx = sliderx - mox;

		

		return;

	}

	if ((mox > (x + SLIDERBEGIN)) && (moy > (y + (h - SLIDERHEIGTH) / 2)) && (mox < (x + w - SLIDERWIDTH)) && (moy < ((y + (h + SLIDERHEIGTH) / 2 + 40)))) {

		sliderx = mox - x - SLIDERBEGIN;

		mainwindow->MySoundStuff->soundpos = 2 * 44100 / 25 * (sliderx + offset);

		slider = sliderx + offset;

		mainwindow->MyAnimationWindow->MyDataObject->update(slider);


	}


	grab = false;

}


void TimeBar::mouseup(int mox, int moy) {

	mousedown = false;

	grab = false;

}

void TimeBar::mousemove(int mox, int moy) {

	tmpx = mox;
	tmpy = moy;


	if (grab) {

		sliderx = mox - x - SLIDERBEGIN;;

		if (sliderx < 0) sliderx = 0;

		if (sliderx > (w - SLIDEREND - SLIDERBEGIN)) sliderx = w -SLIDEREND - SLIDERBEGIN;

		slider = sliderx + offset;


		mainwindow->MyAnimationWindow->MyDataObject->update(slider);

	}

}


void TimeBar::frame_left() {


	if (offset > 0) {

		if (sliderx > 0) {

			sliderx--;

		}
		else {

			offset--;

		}

	}
	else {

		if (sliderx > 0) {

			sliderx--;

		}

	}

	mainwindow->MyAnimationWindow->MyDataObject->update(slider);

}

void TimeBar::frame_right() {

	if (sliderx > (w - SLIDERBEGIN - SLIDEREND)) {

		offset++;

	}
	else {

		sliderx++;


	}

	mainwindow->MyAnimationWindow->MyDataObject->update(slider);

}


bool TimeBar::is_in_slider(int point) {

	int tmpt = point - offset + SLIDERBEGIN;

	return ((tmpt >= SLIDERBEGIN) && (tmpt < (w - SLIDEREND - SLIDERBEGIN)));

}