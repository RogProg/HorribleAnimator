#pragma once

class MainWindow;

class DataObject
{

public:

	DataObject(MainWindow* _mw);


	void deleteCuePoint(int time,int id);

	int storeCuepoint(imagedata* cuepoint, int time, bool undo);

	void update(int time);

	int findPrevCue(int val, int time);
	int findNextCue(int val, int time);

	void SaveAll(WCHAR* filnamn);
	void LoadAll(WCHAR* filnamn);

	void SaveVector(std::vector< imagedata* > , FILE* Fil);
	std::vector< imagedata* > LoadVector(FILE * Fil);

	int getScene(int stime);

	void insert(int frame);
	void remove(int frame);

	MainWindow* mw;

	std::vector< imagedata* > cues;


};

