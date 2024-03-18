
#include "framework.h"
#include "Rotater.h"


Rotater::Rotater(int w, int h , AnimationWindow* _animationwindow ) {

	animationwindow = _animationwindow;

	width = w;
	heigth = h;



	rigth = (double*)malloc(heigth * sizeof(double));
	left  = (double*)malloc(heigth * sizeof(double));

	mxrigth = (double*)malloc(heigth * sizeof(double));
	mxleft = (double*)malloc(heigth * sizeof(double));

	myrigth = (double*)malloc(heigth * sizeof(double));
	myleft = (double*)malloc(heigth * sizeof(double));


};

Rotater::~Rotater() {

	free(rigth);
	free(left);
	free(mxrigth);
	free(mxleft);
	free(myrigth);
	free(myleft);

}


void Rotater::rotateNscale(byte* lmem, int* indexbuffer , int inx , imagedata* id ,double ang, double r , int x, int y, double tint, double scale) {

	double maxy = INT_MIN;
	double miny = INT_MAX;


	double b = 0;

	for (int i = 0; i < heigth; i++) {

		rigth[i] = INT_MIN;
		left[i] = INT_MAX;

	}

	x = (int)(x * scale);
	y = (int)(y * scale);
	

	double mx[4];
	double my[4];


	xx[0] = (id->w / 2.0)*r*scale;
	yy[0] = (id->h / 2.0)*r*scale;
	mx[0] = id->w-1;
	my[0] = id->h-1;


	xx[1] = (id->w / 2.0)*r*scale;
	yy[1] = (-id->h / 2.0)*r*scale;
	mx[1] = id->w-1;
	my[1] = 0;


	xx[2] = (-id->w / 2.0)*r*scale;
	yy[2] = (-id->h / 2.0)*r*scale;
	mx[2] = 0;
	my[2] = 0;



	xx[3] = (-id->w / 2.0)*r*scale;
	yy[3] = (id->h / 2.0)*r*scale;
	mx[3] = 0;
	my[3] = id->h-1;

	
	

	rotate(xx, yy, id->rotposx * id->size*scale, id->rotposy * id->size*scale, id->angle);

	imagedata* loopid = id;

	while (loopid->parent != -1) {

		loopid = animationwindow->imagearr[loopid->parent];

		rotate(xx, yy, (loopid->x + loopid->rotposx * loopid->size - id->x)*scale , (loopid->y + loopid->rotposy * loopid->size - id->y)*scale, loopid->angle);
	
	}

	for (int i = 0; i < 4; i++) {

		xx[i] += x;
		yy[i] += y;

		if (yy[i] > maxy) maxy = (int)yy[i];
		if (yy[i] < miny) miny = (int)yy[i];

	}


	for (int i = 0; i < 4; i++) {

		int ni = (i + 1) % 4;

		double xxx = xx[i];
		double yyy = yy[i];
		double xxn = xx[ni];
		double yyn = yy[ni];

		double mxxx = mx[i];
		double myyy = my[i];
		double mxxn = mx[ni];
		double myyn = my[ni];


		if (yyy > yyn) {

			double tmpx = xxx;
			double tmpy = yyy;

			xxx = xxn;
			yyy = yyn;

			xxn = tmpx;
			yyn = tmpy;


			double tmpmx = mxxx;
			double tmpmy = myyy;

			mxxx = mxxn;
			myyy = myyn;

			mxxn = tmpmx;
			myyn = tmpmy;


		}

		double dx = 0.0;
		double mdx = 0.0;
		double mdy = 0.0;


		if (yyn != yyy) {
						
			dx = (double)(xxn - xxx) / (yyn - yyy);
			mdx = (double)(mxxn - mxxx) / (yyn - yyy);
			mdy = (double)(myyn - myyy) / (yyn - yyy);

		}

		double ppx = xxx;
		

		int startyy = (int)ceil(yyy);
		if (startyy < 0) {

			ppx -= startyy * dx;
			mxxx -= startyy * mdx;
			myyy -= startyy * mdy;

			startyy = 0;

		}

		int endyy = (int)floor(yyn);
		if (endyy >= heigth) endyy = heigth - 1;


		for (int ty = startyy; ty <= endyy; ty++) {

			if (ppx < left[ty]) {

				left[ty] = (int)ppx;

				mxleft[ty] = mxxx;
				myleft[ty] = myyy;

			}

			if (ppx > rigth[ty]) {

				rigth[ty] = (int)ppx;

				mxrigth[ty] = mxxx;
				myrigth[ty] = myyy;

			}

			ppx += dx;

			mxxx += mdx;
			myyy += mdy;

		}

		

	}

	data = id->data;

	int starty = (int)ceil(miny);
	if (starty < 0) starty = 0;

	int endy = (int)floor(maxy);
	if (endy >= heigth) endy = heigth - 1;
	

	for (int i = starty; i <= endy ; i++) {

		int iwidth = i * width;

		double dxmp = 0.0;
		double dymp = 0.0;

		if (rigth[i] != left[i]) {

			dxmp = (mxrigth[i] - mxleft[i]) / (rigth[i] - left[i]);
			dymp = (myrigth[i] - myleft[i]) / (rigth[i] - left[i]);

		}


		double mxp = mxleft[i];
		double myp = myleft[i];


		int startxxx = (int)left[i];
		if (startxxx < 0) {
			
			mxp -= startxxx * dxmp;
			myp -= startxxx * dymp;
		
			startxxx = 0;

		}

		int endxxx = (int)rigth[i];
		if (endxxx >= width) endxxx = width - 1;


		int ofs, ofsm;
		

		for (int j = startxxx; j < endxxx; j++) {

			ofs = (j +  iwidth) * 4;

			ofsm = ((int)mxp + (int)(myp) * id->w) << 2;

			

			if (data[ofsm + 3] != 0) {

				lmem[ofs++] = data[ofsm++];
				lmem[ofs++] = data[ofsm++];
				lmem[ofs] = data[ofsm];
				//	lmem[ofs + 3] = id->data[ofsm + 3];

				indexbuffer[(j + iwidth)] = inx;

			}


			mxp += dxmp;
			myp += dymp;


		}

	}


};


void Rotater::rotate(double* xx, double* yy, double ofsx, double ofsy, double angle) {

	for (int i = 0; i < 4; i++) {

		xx[i] -= ofsx;
		yy[i] -= ofsy;

		double rx = cos(angle) * xx[i] - sin(angle) * yy[i];
		double ry = sin(angle) * xx[i] + cos(angle) * yy[i];

		xx[i] = rx + ofsx;
		yy[i] = ry + ofsy;

	}

}
