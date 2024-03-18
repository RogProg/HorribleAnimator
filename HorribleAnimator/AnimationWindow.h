#pragma once

class MainWindow;

class AnimationWindow : public BaseWindow
{

public:


	AnimationWindow(MainWindow* _mainwindow, int _x, int _y, int _w, int _h);

	void setratio();

	void newScene(int scenetime);

	void selectBackground();

	void changeBackground(int im);

	void gotoPrevCue();

	void gotoNextCue();

	void setCue();

	void resize(int _x, int _y, int _w, int _h);

	void paint();

	void resetbuffer();

	void addimage(imagedata* idata);

	void bind(int parent, int bindto);

	void mouseclick(int mox, int moy);

	void mouseRclick(int mox, int moy);

	void mouseup(int mox, int moy);

	void mouseRup(int mox, int moy);

	void mousemove(int mox, int moy);

	void movechild(int parent, double px, double py, double size);

	double get_size(int child);

	void showmenu(int mmx, int mmy, int sender);

	int getRootParent(int child);

	void showImageChanger();

	void changeImage(int im);

	void update_backgrounds();


	int findPrevScene(int time);
	int findNextScene(int time);

	void gotoNextScene();
	void gotoPrevScene();

	void move_cue_left();
	void move_cue_right();

	int findCue(int sel , int time);

	void change_visible();

	bool is_active();

	Rotater* MyRotater = NULL;

	DataObject* MyDataObject;

	bool play = false;


	double mx,my,oldx,oldy;

	int selected = -1;
	int menuselect = -1;
	int move = -1;

	bool mousedown = false;

	bool sizedrag = false;
	bool rotposdrag = false;
	bool rotdrag = false;
	bool drag;

	HCURSOR crossCursor;

	bool cross = false;

	std::vector< imagedata* > imagearr;
	std::vector< imagedata* > sortarr;
	std::vector< imagedata* > background;


	
	WCHAR wc0[40] = L"Select child";
	WCHAR wc1[40] = L"Change image";
	WCHAR wc2[40] = L"Set Cuepoint";
	WCHAR wc3[40] = L"Goto prev Cuepoint";
	WCHAR wc4[40] = L"Goto next Cuepoint";
	WCHAR wc5[40] = L"Show/Hide";

	textdata td[6];

	int* indexbuffer;
	int* indexbufferbase;

	int controlx, controly;

	int tmpx, tmpy;

	int ictmpx, ictmpy;

	int rpx, rpy;
	int rx, ry;
	int sx, sy;

	double oldsize,oldrot;

	const int OBJECTWINSENDER = 1;
	const int AINIMATIONWINDOWSENDER = 2;
	const int NEWBACKGROUNDSENDER = 3;

	double xx[4];
	double yy[4];

	int currscene = 0;

	

	int vieww, viewh;


	const int HDW = 1280;
	const int HDH = 720;

	const double HDRATIO = (double)HDW / HDH;

	double ratio;

	int boxx1, boxy1, boxx2, boxy2;

	


};

