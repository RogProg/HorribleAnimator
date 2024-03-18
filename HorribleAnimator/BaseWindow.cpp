#include "framework.h"
#include "BaseWindow.h"


BaseWindow::BaseWindow(MainWindow* _mainwindow, int _x, int _y, int _w, int _h) {

	mainwindow = _mainwindow;

	

    x = _x;
    y = _y;
    w = _w;
    h = _h;

    size.width = (UINT32)w;
    size.height = (UINT32)h;

	lmem = (byte*)malloc(w * h * 4);

    dxstuff = mainwindow->MyDxstuff;

    dxstuff->m_pRenderTarget->CreateBitmap(size,
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE)), &pBitmap);
            
            
    

}

BaseWindow::~BaseWindow() {


    delete(lmem);


}

bool BaseWindow::isIn(int px,int py) {

    return ((px > x) && (py > y) && (px < (x + w)) && (py < (y + h)));

}

void BaseWindow::resize(int _x, int _y, int _w, int _h) {


    x = _x;
    y = _y;
    w = _w;
    h = _h;

    size.width = w;
    size.height = h;

    free(lmem);

    lmem = (byte*)malloc(w * h * 4);

    dxstuff = mainwindow->MyDxstuff;

    dxstuff->m_pRenderTarget->CreateBitmap(size,
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE)), &pBitmap);


}

void BaseWindow::addtext(textdata* td) {

    texter.push_back(td);

}


void BaseWindow::drawit() {


    pBitmap->CopyFromMemory(nullptr, lmem, size.width * 4);
    
    
    //dxstuff->m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Blue));


    dxstuff->m_pRenderTarget->DrawBitmap(pBitmap, //the bitmap to draw [a portion of],
        D2D1::RectF((float)x, (float)y, (float)(x+w),(float)(y+h)), //destination rectangle,
        1.0f, //alpha blending multiplier,
        D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, //interpolation mode,
        D2D1::RectF(0, 0, (float)size.width, (float)size.height)); //source rectangle

    
    for (int i = 0; i < texter.size(); i++) {


        textdata* td = (textdata*)texter[i];


        dxstuff->m_pRenderTarget->DrawText(
            td->text,
            (int)wcslen(td->text),
            dxstuff->m_pTextFormat,
            D2D1::RectF((float)td->x, (float)td->y, (float)mainwindow->MyDxstuff->size.width, (float)mainwindow->MyDxstuff->size.height),
            dxstuff->m_pD2DBrush
        );
    }
    
        



}



