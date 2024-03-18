#pragma once

class MainWindow;

class BaseWindow
{
public:

	BaseWindow(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);
	~BaseWindow();

	void resize(int _x, int _y, int _w, int _h);

	void drawit();

	void addtext(textdata* td);

	bool isIn(int px, int py);

	MainWindow* mainwindow;

	ID2D1Bitmap* pBitmap;

	Dxstuff* dxstuff;


	bool mousedown, grab;

	int x, y, w, h;

	D2D1_SIZE_U size;
	
	byte* lmem;

	std::vector< textdata* > texter;

	bool paintnow;

};

