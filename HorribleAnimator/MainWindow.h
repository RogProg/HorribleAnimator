#pragma once
class MainWindow
{

public:

	MainWindow(HWND _hWnd);

	void resize();

	void paint();
	void drawit();

	void mouseclick(int mox, int moy);
	void mouseRclick(int mox, int moy);
	void mouseup(int mox, int moy);
	void mouseRup(int mox, int moy);
	void mousemove(int mox, int moy);



	const int OBJECTWINSENDER = 1;



	HWND hWnd;

	Dxstuff* MyDxstuff;

	Encoder* MyEncoder;

	Browser* MyBrowser;
	AnimationWindow* MyAnimationWindow;
	TimeBar* MyTimeBar;
	ObjectWindow* MyObjectWindow;
	ImageChanger* MyImageChanger;

	Floater* MyFloater;

	Menu* MyMenu;

	Message* MyMessage;

	SoundStuff* MySoundStuff;

	UndoClass* MyUndoClass;

	//Mpeg* MyMpeg;

	double t;

	bool menuup = false;
	bool imagechangerup = false;
	bool messageup = false;




	const int BROWSERWIDTH = 200;
	const int TIMERBARHEIGHT = 100;
	const int OBJECTWINDOWWIDTH = 200;

};

