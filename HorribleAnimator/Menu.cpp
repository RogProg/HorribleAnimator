#include "framework.h"
#include "Menu.h"



Menu::Menu(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) : BaseWindow(_mainwindow, _x, _y, _w, _h) {

    
    

};


void Menu::paint() {


    mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0, 0, w, h, 255, 255, 255);

    if (hint != -1)
        mainwindow->MyDxstuff->MyGfxTools->drawRect(lmem, w, 0,hint*24, w, 24, 200, 200, 200);

    mainwindow->MyDxstuff->MyGfxTools->drawBox(lmem, w, h,  0, 0, w - 1, h - 1, 0, 0, 0);

    for (int i = 1; i < texter.size(); i++) {

        mainwindow->MyDxstuff->MyGfxTools->drawHLine(lmem, w, h ,  0, w, i * 24, 0, 0, 0);

    }

}

void Menu::setsize() {

    hint = -1;

    w = 250;
    h = (int)texter.size() * 24;
   

    size.width = w;
    size.height = h;

    lmem = (byte*)malloc(w * h * 4);


    for (int i = 0; i < texter.size(); i++) {

        texter[i]->x = x + 10;
        texter[i]->y = y + i * 24;


    }


    dxstuff->m_pRenderTarget->CreateBitmap(size,
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE)), &pBitmap);


}

void Menu::mouseRup(int mox, int moy) {

    for (int i = 0; i < texter.size(); i++) {

        if ((mox > x) && (moy > (y + i * 24)) && (mox < (x + w)) && (moy < (y + (i + 1) * 24))) { 
            
            if (texter[i]->sender == BROWSERSENDER) {

                if (i == 0) {

                    mainwindow->MyBrowser->loadfile(mainwindow->MyBrowser->loadsel);

                    return;
                }

                if (i == 1) {

                    mainwindow->MyAnimationWindow->changeBackground(mainwindow->MyBrowser->loadsel);

                    return;
                }

                return;

            }


            if (texter[i]->sender == OBJECTWINSENDER) {

                if (i == 0) {
                                        
                    mainwindow->MyAnimationWindow->cross = true;
                }

                if (i == 1) {

                    mainwindow->MyObjectWindow->showImageChanger();

                }

                if (i == 2) {

                    mainwindow->MyAnimationWindow->menuselect = mainwindow->MyObjectWindow->selected;

                    mainwindow->MyAnimationWindow->setCue();

                }

                if (i == 3) {

                    mainwindow->MyAnimationWindow->selected = mainwindow->MyObjectWindow->selected;

                    mainwindow->MyAnimationWindow->gotoPrevCue();

                }


                if (i == 4) {

                    mainwindow->MyAnimationWindow->selected = mainwindow->MyObjectWindow->selected;

                    mainwindow->MyAnimationWindow->gotoNextCue();

                }


                if (i == 5) {

                    mainwindow->MyObjectWindow->moveUp();

                }
                
                if (i == 6) {

                    mainwindow->MyObjectWindow->moveDown();

                }

                if (i == 7) {

                    mainwindow->MyAnimationWindow->menuselect = mainwindow->MyObjectWindow->selected;

                    mainwindow->MyAnimationWindow->change_visible();

                }

            }
            
            if (texter[i]->sender == AINIMATIONWINDOWSENDER) {
            
                if (i == 0) {

                    mainwindow->MyAnimationWindow->cross = true;

                }


                if (i == 1) {

                    mainwindow->MyAnimationWindow->showImageChanger();

                }

                if (i == 2) {

                    mainwindow->MyAnimationWindow->setCue();

                }

                if (i == 3) {

                    mainwindow->MyAnimationWindow->gotoPrevCue();

                }
                

                if (i == 4) {

                    mainwindow->MyAnimationWindow->gotoNextCue();

                }

                if (i == 5) {

                    mainwindow->MyAnimationWindow->change_visible();

                }


                //mainwindow->MyAnimationWindow->bind(mox,moy);


            }


        }


    }

}

void Menu::mousemove(int mox, int moy) {

    

    for (int i = 0; i < texter.size(); i++) {

        if ((mox > x) && (moy > (y + i * 24)) && (mox < (x + w)) && (moy < (y + (i + 1) * 24))) {

            hint = i;

            return;

        }

    }

    hint = -1;

}