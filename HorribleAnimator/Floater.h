#pragma once

class MainWindow;

class Floater : public BaseWindow
{

public:


	Floater(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {};

	void paint(imagedata* id);



};

