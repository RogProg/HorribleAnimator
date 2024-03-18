#pragma once
class GfxTools
{

public:

	GfxTools();
	 
	void drawRect(byte* lmem,int w , int x, int y, int width, int heigth, byte r, byte g, byte b);

	void drawVLine(byte* lmem, int w, int h, int x, int y, int y2, byte r, byte g, byte b);

	void drawHLine(byte* lmem, int w, int h ,int x, int x2, int y, byte r, byte g, byte b);

	void drawBox(byte* lmem, int w, int h, int x, int y, int x2, int y2, byte r, byte g, byte b);

	void drawLine(byte* lmem, int w, int h, int x, int y, int x2, int y2, byte r, byte g, byte b);

};

