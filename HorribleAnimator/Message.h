#pragma once
#include "BaseWindow.h"

class MainWindow;

class Message : public BaseWindow
{
public:

	Message(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);

	void paint();

	void showMessage(WCHAR* txt);

	void setText(WCHAR* txt);

	void mouseclick(int mox, int moy);

	void mouseup(int mox, int moy);



};

