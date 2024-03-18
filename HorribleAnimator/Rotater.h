#pragma once

class AnimationWindow;

class Rotater
{


public:

	Rotater(int w, int h, AnimationWindow* _animationwindow);
	~Rotater();



	void rotateNscale(byte* lmem,int* indexbuffer, int inx, imagedata* id, double ang, double r, int x, int y, double tint, double scale);

	void rotate(double* xx, double* yy, double ofsx, double ofsy, double angle);

	int width, heigth;

	double *left, *rigth;
	double* mxleft, * mxrigth;
	double* myleft, * myrigth;

	double xx[4];
	double yy[4];

	byte* data;

	AnimationWindow* animationwindow;

};

