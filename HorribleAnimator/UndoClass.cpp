#include "framework.h"
#include "UndoClass.h"

UndoClass::UndoClass(MainWindow* _mainwindow) {

	MyMainWindow = _mainwindow;

}

void UndoClass::store_newimage(int img, int cuenr1,int cuenr2) {


	UndoInfo* ud = (UndoInfo*)malloc(sizeof(UndoInfo));

	ud->type = 2;

	ud->img = img;

	ud->cuenr1 = cuenr1;

	ud->cuenr2 = cuenr2;

	undovector.push_back(ud);
	

}


void UndoClass::store_delete_cue(int time, int id) {


	imagedata* found = NULL;

	for (imagedata* cue : MyMainWindow->MyAnimationWindow->MyDataObject->cues) {

		if ((cue->time == time) && (cue->id == id)) {

			found = cue;

			break;

		}

	}

	if (found == NULL) MessageBox(MyMainWindow->hWnd, L"Cue not found!", L"Error", MB_OK);

	UndoInfo* ud = (UndoInfo*)malloc(sizeof(UndoInfo));
	
	ud->data = found;

	ud->time = found->time;

	ud->type = 0;

	undovector.push_back(ud);

}

void UndoClass::store_inserted_cue(imagedata* cue, int cuenr,imagedata* olddata) {

	UndoInfo* ud = (UndoInfo*)malloc(sizeof(UndoInfo));

	ud->type = 1;

	ud->cuenr1 = cuenr;

	ud->time = MyMainWindow->MyAnimationWindow->MyDataObject->cues[cuenr]->time;

	ud->data = MyMainWindow->MyAnimationWindow->MyDataObject->cues[cuenr];

	
	ud->olddata = olddata;
		
	
	undovector.push_back(ud);

}



void UndoClass::restore_last() {

	if (undovector.size() != 0) {

		UndoInfo* ud = undovector.back();
		undovector.pop_back();

		if (ud->type == 0) {

			MyMainWindow->MyTimeBar->set_slider(ud->time);

			MyMainWindow->MyAnimationWindow->MyDataObject->update(ud->time);

			MyMainWindow->MyAnimationWindow->MyDataObject->storeCuepoint(ud->data, ud->data->time,false);

			MyMainWindow->MyAnimationWindow->MyDataObject->update(MyMainWindow->MyTimeBar->slider);

		}

		if (ud->type == 1) {
			
			MyMainWindow->MyTimeBar->set_slider(ud->time);

			if (ud->olddata != NULL) {

				memcpy(MyMainWindow->MyAnimationWindow->MyDataObject->cues[ud->cuenr1], ud->olddata, sizeof(imagedata));

			}
			else {

				MyMainWindow->MyAnimationWindow->MyDataObject->cues.erase(MyMainWindow->MyAnimationWindow->MyDataObject->cues.begin() + ud->cuenr1);

			}
			
			MyMainWindow->MyAnimationWindow->MyDataObject->update(MyMainWindow->MyTimeBar->slider);


		}

		if (ud->type == 2) {

			if (ud->img == MyMainWindow->MyAnimationWindow->selected)
				MyMainWindow->MyAnimationWindow->selected = -1;

			MyMainWindow->MyAnimationWindow->MyDataObject->cues.erase(MyMainWindow->MyAnimationWindow->MyDataObject->cues.begin() + ud->cuenr1);

			if (ud->cuenr2 != -1)
				MyMainWindow->MyAnimationWindow->MyDataObject->cues.erase(MyMainWindow->MyAnimationWindow->MyDataObject->cues.begin() + ud->cuenr2);

			MyMainWindow->MyAnimationWindow->imagearr.pop_back();

			MyMainWindow->MyObjectWindow->imagearr.pop_back();

			MyMainWindow->MyAnimationWindow->MyDataObject->update(MyMainWindow->MyTimeBar->slider);

		}

		

	}

}