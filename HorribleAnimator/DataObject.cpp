
#include "framework.h"
#include "DataObject.h"


DataObject::DataObject(MainWindow* _mw) {


	mw = _mw;


}

void DataObject::deleteCuePoint(int time,int id) {

	
	for (int i = 0 ; i < cues.size() ; i++ ) {

		if ((cues[i]->time == time ) && ( cues[i]->id == id)) {

			mw->MyUndoClass->store_delete_cue(time, id);

			cues.erase(cues.begin() + i);

			return;

		}

	}

}

int DataObject::storeCuepoint(imagedata* cuepoint, int time,bool undo) {

	imagedata* foundid = nullptr;

	int cuenr = 0;

	for (imagedata* searchid : cues) {

		if ((searchid->id == cuepoint->id) && (searchid->time == time)) {

			foundid = searchid;
						
			break;
		}

		cuenr++;

	}

	imagedata* olddata = NULL;

	imagedata* id;

	if (foundid == nullptr) {

		id = new imagedata;

	}
	else {

		id = foundid;

		olddata = new imagedata;

		memcpy(olddata, foundid, sizeof(imagedata));

	}
		
	memcpy(id, cuepoint, sizeof(imagedata));

	id->time = time;

	if (foundid == nullptr) {

		cues.push_back(id);

		if (undo) mw->MyUndoClass->store_inserted_cue(cues[cues.size()-1], (int)cues.size() - 1,NULL);

	} else {

		if (undo) mw->MyUndoClass->store_inserted_cue(cues[cuenr], cuenr,olddata);

	}

	return ((int)cues.size() - 1);

}

void DataObject::update(int time) {

	
	int scene = getScene(time);


	for (int i = 0; i < mw->MyAnimationWindow->imagearr.size() ; i++) {


		int currid =  mw->MyAnimationWindow->imagearr[i]->id;

		


	    int starttime = 0;
		int endtime = INT_MAX;

		imagedata* startid = nullptr;
		imagedata* endid = nullptr;

		for (imagedata* id : cues) {

			if ((id->id == currid) && (id->scene == scene)) {

				if ((id->time >= starttime) && (id->time <= time)) {

					starttime = id->time;

					startid = id;

					}

				if ((id->time <= endtime) && (id->time >= time)) {

					endtime = id->time;

					endid = id;

				}
			}

		}

		if ((startid != nullptr) && (endid != nullptr)) {

			double dt = (endid->time - startid->time);

			if (dt == 0) dt = 1.0;

			if (mw->MyAnimationWindow->imagearr[currid]->parent == -1) {

				double dx = (double)(endid->x - startid->x) / dt;
				double dy = (double)(endid->y - startid->y) / dt;

				mw->MyAnimationWindow->imagearr[currid]->x = startid->x + dx * (time - startid->time);
				mw->MyAnimationWindow->imagearr[currid]->y = startid->y + dy * (time - startid->time);

			}
			else {

				double dx = (double)(endid->ofsx - startid->ofsx) / dt;
				double dy = (double)(endid->ofsy - startid->ofsy) / dt;

				mw->MyAnimationWindow->imagearr[currid]->ofsx = startid->ofsx + dx * (time - startid->time);
				mw->MyAnimationWindow->imagearr[currid]->ofsy = startid->ofsy + dy * (time - startid->time);

			}

			double ds = (double)(endid->ownsize - startid->ownsize) / dt;

			double siz = startid->ownsize + ds * (time - startid->time);

			
			mw->MyAnimationWindow->imagearr[currid]->ownsize = siz;




			ds = (double)(endid->size - startid->size) / dt;

			siz = startid->size + ds * (time - startid->time);

			mw->MyAnimationWindow->imagearr[currid]->size = siz;



			double da = (double)(endid->angle - startid->angle) / dt;

			mw->MyAnimationWindow->imagearr[currid]->angle = startid->angle + da * (time - startid->time);

		}

		if ((startid != nullptr) && (endid == nullptr)) {

			mw->MyAnimationWindow->imagearr[currid]->x = startid->x;
			mw->MyAnimationWindow->imagearr[currid]->y = startid->y;

			mw->MyAnimationWindow->imagearr[currid]->ofsx = startid->ofsx;
			mw->MyAnimationWindow->imagearr[currid]->ofsy = startid->ofsy;

			mw->MyAnimationWindow->imagearr[currid]->size = startid->size;
			mw->MyAnimationWindow->imagearr[currid]->ownsize = startid->ownsize;

			mw->MyAnimationWindow->imagearr[currid]->angle = startid->angle;

		}

		
		if (startid != nullptr) {

			mw->MyAnimationWindow->imagearr[currid]->data = mw->MyDxstuff->arr[startid->imagelink]->data;
			mw->MyAnimationWindow->imagearr[currid]->w = mw->MyDxstuff->arr[startid->imagelink]->w;
			mw->MyAnimationWindow->imagearr[currid]->h = mw->MyDxstuff->arr[startid->imagelink]->h;

			mw->MyAnimationWindow->imagearr[currid]->visible = startid->visible;

		}
		

		int rootparent = mw->MyAnimationWindow->getRootParent(currid);

		mw->MyAnimationWindow->movechild(rootparent, mw->MyAnimationWindow->imagearr[rootparent]->x, mw->MyAnimationWindow->imagearr[rootparent]->y, mw->MyAnimationWindow->imagearr[rootparent]->size );

	}


}


int DataObject::findPrevCue(int val,int time) {

	bool found = false;

	int starttime = -1;

	for (imagedata* id : cues) {

		if ((id->id == val) && (id->time > starttime) && (id->time < time)) {

			starttime = id->time;

			found = true;

		}

	}

	if (!found) return -1;

	return starttime;

}


int DataObject::findNextCue(int val, int time) {

	bool found = false;

	int endtime = INT_MAX;

	for (imagedata* id : cues) {

		if ((id->id == val) && (id->time < endtime) && (id->time > time)) {

			endtime = id->time;

			found = true;

		}

	}

	if (!found) return -1;

	return endtime;

}


void DataObject::SaveAll(WCHAR* filnamn) {


	if (mw->MySoundStuff->data_size == 0) {

		MessageBox(mw->hWnd, L"Load Wav file first!", L"Warning", MB_OK);

		return;

	}


	FILE* pFile;

	_wfopen_s(&pFile,filnamn, L"wb");


	SaveVector(cues, pFile);
	SaveVector(mw->MyDxstuff->arr, pFile);
	SaveVector(mw->MyAnimationWindow->imagearr, pFile);
	SaveVector(mw->MyAnimationWindow->background, pFile);
	

	fwrite(&mw->MyTimeBar->endpoint, 1, sizeof(int), pFile);


	int bytes = (int)mw->MyDxstuff->arr.size();

	fwrite(&bytes, 1, sizeof(int), pFile);

	for (imagedata* id : mw->MyDxstuff->arr) {

		int bytes = id->w * id->h * 4;

		fwrite(&bytes, 1, sizeof(bytes), pFile);

		fwrite(id->data, 1, bytes, pFile);

	}

	fwrite(mw->MySoundStuff->info,sizeof(wavinfo),1,pFile);

	bytes = mw->MySoundStuff->data_size;

	fwrite(&bytes, 1, sizeof(int),pFile);

	fwrite((byte*)mw->MySoundStuff->data, 1, bytes, pFile);

	fclose(pFile);

}


void DataObject::LoadAll(WCHAR* filnamn) {

	mw->MyObjectWindow->imagearr.clear();

	

		FILE* pFile;

		_wfopen_s(&pFile,filnamn, L"rb");

	
	cues = LoadVector(pFile);
	mw->MyDxstuff->arr = LoadVector(pFile);
	mw->MyAnimationWindow->imagearr = LoadVector(pFile);
	mw->MyAnimationWindow->background = LoadVector(pFile);


	
	fread(&mw->MyTimeBar->endpoint, 1, sizeof(int), pFile);
	

	int nrimages = 0;
	int bytes = 0;

	fread(&nrimages,1,sizeof(int),pFile);

	byte* data;

	for (int i = 0; i < nrimages; i++) {

		
		fread(&bytes, 1, sizeof(int), pFile);

	    data = (byte*)malloc(bytes);

		fread(data, 1, bytes, pFile);

		mw->MyDxstuff->arr[i]->data = data;

		mw->MyObjectWindow->imagearr.push_back(mw->MyDxstuff->arr[i]);

	}

	mw->MySoundStuff->info = (wavinfo*)malloc(sizeof(wavinfo));

	fread(mw->MySoundStuff->info,sizeof(wavinfo),1,pFile);
	
	mw->MySoundStuff->size = mw->MySoundStuff->info->data_size / sizeof(short);

	fread(&bytes, 1, sizeof(int), pFile);

	mw->MySoundStuff->data = (INT16*)malloc(bytes);

	fread(mw->MySoundStuff->data, 1, bytes, pFile);

	mw->MySoundStuff->data_size = bytes;

	mw->MySoundStuff->size = mw->MySoundStuff->data_size / sizeof(short);

	mw->MySoundStuff->reset();
	
	fclose(pFile);


	for (int currid = 0; currid < mw->MyAnimationWindow->imagearr.size(); currid++) {

		mw->MyAnimationWindow->imagearr[currid]->data = mw->MyDxstuff->arr[mw->MyAnimationWindow->imagearr[currid]->imagelink]->data;
		mw->MyAnimationWindow->imagearr[currid]->w = mw->MyDxstuff->arr[mw->MyAnimationWindow->imagearr[currid]->imagelink]->w;
		mw->MyAnimationWindow->imagearr[currid]->h = mw->MyDxstuff->arr[mw->MyAnimationWindow->imagearr[currid]->imagelink]->h;

	}


	mw->MyAnimationWindow->update_backgrounds();

}

void DataObject::SaveVector(std::vector< imagedata* > v, FILE* Fil) {

	int bytes = (int)v.size();

	fwrite(&bytes, 1, sizeof(int), Fil);

	for (imagedata* id : v) {

		fwrite(id, 1, sizeof(imagedata) - sizeof(byte*), Fil);

		/*
		fwrite(&id->time, 1, sizeof(int), Fil);
		fwrite(&id->w, 1, sizeof(int), Fil);
		fwrite(&id->h, 1, sizeof(int), Fil);
		fwrite(&id->ch, 1, sizeof(int), Fil);
		fwrite(&id->x, 1, sizeof(int), Fil);
		fwrite(&id->y, 1, sizeof(int), Fil);
		fwrite(&id->sw, 1, sizeof(int), Fil);
		fwrite(&id->sh, 1, sizeof(int), Fil);
		fwrite(&id->ofsx, 1, sizeof(int), Fil);
		fwrite(&id->ofsy, 1, sizeof(int), Fil);
		fwrite(&id->rotposx, 1, sizeof(int), Fil);
		fwrite(&id->rotposy, 1, sizeof(int), Fil);
		fwrite(&id->angle, 1, sizeof(double), Fil);
		fwrite(&id->size, 1, sizeof(double), Fil);
		fwrite(&id->ownsize, 1, sizeof(double), Fil);
		fwrite(&id->tmpw, 1, sizeof(double), Fil);
		fwrite(&id->id, 1, sizeof(int), Fil);
		fwrite(&id->aspect, 1, sizeof(double), Fil);
		fwrite(&id->layer, 1, sizeof(int), Fil);
		fwrite(&id->parent, 1, sizeof(int), Fil);
		fwrite(&id->imagelink, 1, sizeof(int), Fil);
		fwrite(&id->scene, 1, sizeof(int), Fil);
		*/

	}


}

std::vector< imagedata* > DataObject::LoadVector(FILE* Fil) {

	std::vector< imagedata* > tmpv;

	tmpv.clear();

	int bytes = 0;


	fread(&bytes, 1, sizeof(int), Fil);

	for (int i = 0; i < bytes; i++) {

		imagedata* indata = new imagedata;


		fread(indata, 1, sizeof(imagedata) - sizeof(byte*), Fil);

		/*
		fread(&indata->time, 1, sizeof(int), Fil);
		fread(&indata->w, 1, sizeof(int), Fil);
		fread(&indata->h, 1, sizeof(int), Fil);
		fread(&indata->ch, 1, sizeof(int), Fil);
		fread(&indata->x, 1, sizeof(imagedata), Fil);
		fread(&indata->y, 1, sizeof(imagedata), Fil);
		fread(&indata->sw, 1, sizeof(int), Fil);
		fread(&indata->sh, 1, sizeof(int), Fil);
		fread(&indata->ofsx, 1, sizeof(int), Fil);
		fread(&indata->ofsy, 1, sizeof(int), Fil);
		fread(&indata->rotposx, 1, sizeof(int), Fil);
		fread(&indata->rotposy, 1, sizeof(int), Fil);
		fread(&indata->angle, 1, sizeof(double), Fil);
		fread(&indata->size, 1, sizeof(double), Fil);
		fread(&indata->ownsize, 1, sizeof(double), Fil);
		fread(&indata->tmpw, 1, sizeof(double), Fil);
		fread(&indata->id, 1, sizeof(int), Fil);
		fread(&indata->aspect, 1, sizeof(double), Fil);
		fread(&indata->layer, 1, sizeof(int), Fil);
		fread(&indata->parent, 1, sizeof(int), Fil);
		fread(&indata->imagelink, 1, sizeof(int), Fil);
		fread(&indata->scene, 1, sizeof(int), Fil);
		*/
		indata->data = NULL;

		tmpv.push_back(indata);

	}

	return tmpv;

}


int DataObject::getScene(int stime) {

	int scene = 0;

	int startscene = 0;

	for (int i = 0; i < mw->MyAnimationWindow->background.size(); i++) {

		if ((mw->MyAnimationWindow->background[i]->time >= startscene) && (mw->MyAnimationWindow->background[i]->time <= stime)) {

			startscene = mw->MyAnimationWindow->background[i]->time;

			scene = i;

		}

	}

	return scene;

}


void DataObject::insert(int frame) {

	for (imagedata* id : cues) {

		if (id->time > frame) id->time += 1;

	}

}

void DataObject::remove(int frame) {

	for (imagedata* id : cues) {

		if (id->time == frame) {

			return;

		}

	}

	for (imagedata* id : cues) {

		if (id->time > frame) id->time -= 1;

	}


}