#include "framework.h"
#include "Floater.h"



void Floater::paint(imagedata* id) {

	
	mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 200, 200, 200);

	mainwindow->MyDxstuff->drawbitmapscaleQuick(lmem, w,h,-1, id, 0,0,0.8);

	
}
