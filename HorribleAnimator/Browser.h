#pragma once

class MainWindow;

class Browser : public BaseWindow
{

public:

	Browser(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);
		
	void find_number();

	void resize(int _x, int _y, int _w, int _h);

	void paint();

	void mouseclick(int mox, int moy);

	void mouseup(int mox, int moy);

	void mousemove(int mox, int moy);

	void mouseRclick(int mox, int moy);
	
	bool hit(int mox, int moy, int xx, int yy);
	
	void showmenu(int mmx, int mmy);

	void loadfile(int indx);

	WCHAR wc0[40] = L"Load Image";
	WCHAR wc1[40] = L"Set background";

	textdata td[2];


	int selected = -1;

	int loadsel = -1;

	int sx, sy;

	int starth = 0;
	int bh;

};

