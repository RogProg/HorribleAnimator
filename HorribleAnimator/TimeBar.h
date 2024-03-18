#pragma once

class MainWindow;

class TimeBar : public BaseWindow
{
public:


	TimeBar(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);
	
	void resize(int _x, int _y, int _w, int _h);

	void drawit();

	void set_slider(int s);

	void paint();

	void mouseclick(int mox, int moy);

	void mouseup(int mox, int moy);

	void mousemove(int mox, int moy);

	int getScene(int stime);

	void frame_right();
	void frame_left();

	bool is_in_slider(int point);


	bool mousedown = false;
	bool grab = false;

	int tmpx, tmpy;

	int mx;

	int slider = 0;
	int sliderx = 0;

	textdata* frametext;

	const int SLIDERWIDTH = 16;
	const int SLIDERHEIGTH = 32;
	const int SLIDERBEGIN = 20;
	const int SLIDEREND = 180;

	int slidermax;

	int offset,nrl;

	int endpoint = 0;

	

};

