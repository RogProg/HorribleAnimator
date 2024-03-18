#pragma once

class MainWindow;

class Menu : public BaseWindow
{

public:

	Menu(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);


	void paint();

	void setsize();




	void mouseclick(int mox, int moy);

	void mouseRup(int mox, int moy);

	void mousemove(int mox, int moy);


	int hint;

	

	const int OBJECTWINSENDER = 1;
	const int AINIMATIONWINDOWSENDER = 2;


};