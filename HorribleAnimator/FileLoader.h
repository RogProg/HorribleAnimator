#pragma once



class FileLoader
{

public:


	FileLoader();
	~FileLoader();

	imagedata* loadfile(WCHAR* filename);

	int w, h , ch;

	byte* mem;

	FreeImageIO io;

};

