#pragma once
#include "BaseWindow.h"

class MainWindow;

class ImageChanger : public BaseWindow
{

public:

	ImageChanger(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);

	void resize(int _x, int _y, int size);

	

	void paint();

	void mouseclick(int mox, int moy);
	void mouseup(int mox, int moy); 


	int selected;

	int source;

	int xx, yy;

	int sw, sh,starth;

	

};

