#pragma once

class MainWindow;

class ObjectWindow : public BaseWindow
{

public:


		ObjectWindow(MainWindow * _mainwindow, int _x, int _y, int _w, int _h);

		void resize(int _x, int _y, int _w, int _h);

		void find_number();

		void paint();

		void addimage(imagedata* idata);

		void moveUp();
		void moveDown();


		void mouseclick(int mox, int moy);

		void mouseRclick(int mox, int moy);

		void mouseup(int mox, int moy);

		void mouseRup(int mox, int moy);

		void mousemove(int mox, int moy);

		int findId(int i);

		bool hit(int mox, int moy, int xx, int yy);

		void showImageChanger();

		void changeImage(int im);

		void showmenu(int mmx, int mmy);

		textdata* frametext;

		std::vector< imagedata* > imagearr;

		WCHAR wc0[20] = L"Select child";
		WCHAR wc1[20] = L"Change image";
		WCHAR wc2[20] = L"Set Cuepoint";
		WCHAR wc3[20] = L"Goto prev Cuepoint";
		WCHAR wc4[20] = L"Goto next Cuepoint";
		WCHAR wc5[20] = L"Move up";
		WCHAR wc6[20] = L"Move down";
		WCHAR wc7[20] = L"Show/Hide";
		


		textdata td[8];


		int selected;



		int starth = 0;
		int bh;

		int tmpmox, tmpmoy;

		double load;

};

