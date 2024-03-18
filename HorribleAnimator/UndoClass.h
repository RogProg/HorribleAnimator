#pragma once

class MainWindow;

class UndoClass
{
public:

	UndoClass(MainWindow* _mainwindow);

	void store_newimage(int img, int cuenr1, int cuenr2);
	void store_delete_cue(int time, int id);
	void store_inserted_cue(imagedata* cue, int cuenr,imagedata* olddata);
	void restore_last();

	MainWindow* MyMainWindow;

	std::vector< UndoInfo* > undovector;

};

