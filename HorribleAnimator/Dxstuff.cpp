
#include "framework.h"
#include "Dxstuff.h"



Dxstuff::Dxstuff(HWND _hWnd, MainWindow* _mainwindow) {

    hWnd = _hWnd;

    mainwindow = _mainwindow;

    createDevices();

    MyGfxTools = new  GfxTools();

    //MyFileLoader = new FileLoader();

    MyBMPLoader = new BMPLoader();

    GetCurrentDirectoryW(MAX_PATH,DIR);

    
    swprintf_s(Fil, lstrlenW(DIR) + lstrlenW(controlfile) + 2, L"%s\\%s", DIR, controlfile);

    
    controlimg = MyBMPLoader->loadfile(Fil);
    
    if (controlimg == 0) {

        MessageBoxW(mainwindow->hWnd, Fil, L"Error", MB_OK);

        exit;
    
    }



    swprintf_s(Fil, lstrlenW(DIR) + lstrlenW(up) + 2, L"%s\\%s", DIR, up);

    upimg = MyBMPLoader->loadfile(Fil);

    swprintf_s(Fil, lstrlenW(DIR) + lstrlenW(down) + 2, L"%s\\%s", DIR, down);

    downimg = MyBMPLoader->loadfile(Fil);



    swprintf_s(Fil, lstrlenW(DIR) + lstrlenW(okfile) + 2, L"%s\\%s", DIR, okfile);

    okimg = MyBMPLoader->loadfile(Fil);
   
};







Dxstuff::~Dxstuff() {

    SafeRelease(&m_pDirect2dFactory);
    SafeRelease(&m_pRenderTarget);


};


void Dxstuff::createDevices() {


    HRESULT hr = S_OK;


    if (m_pDirect2dFactory != NULL)
        SafeRelease(&m_pDirect2dFactory);

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

    RECT rc;
    GetClientRect(hWnd, &rc);

    size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top);


    if (m_pRenderTarget != NULL)
        SafeRelease(&m_pRenderTarget);

    hr = m_pDirect2dFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hWnd, size),
        &m_pRenderTarget);




    m_pRenderTarget->CreateBitmap(size,
        D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM,
            D2D1_ALPHA_MODE_IGNORE)), &pBitmap);



    static const WCHAR msc_fontName[] = L"Verdana";
    static const FLOAT msc_fontSize = 20;


    hr = DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&pDWriteFactory)
    );

    hr = pDWriteFactory->CreateTextFormat(
        msc_fontName,
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        msc_fontSize,
        L"", //locale
        &m_pTextFormat
    );


    hr = pDWriteFactory->CreateTextFormat(
        msc_fontName,
        NULL,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        10,
        L"", //locale
        &m_pTextFormatTime
    );

    // Center the text horizontally and vertically.
// m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

 //m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


    m_pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black, 1.0f),
        &m_pD2DBrush
    );

}

/*

void Dxstuff::addtext(WCHAR* txt, int _x, int _y) {

    textdata* tmp = (textdata*)malloc(sizeof(textdata));

    wcsncpy_s(tmp->text, 1000, txt, wcslen(txt));


    tmp->x = _x;
    tmp->y = _y;

    texter.push_back(tmp);

}
*/


void Dxstuff::paint(double t) {


    //drawbitmapscaleQuick((imagedata*)arr[0], 0, 0, 301+sin(t)*300, 301 + sin(t) * 300);

    //drawbitmapscale((imagedata*)arr[0], 0, 0, 301 + sin(t) * 300, 301 + sin(t) * 300);

    //drawbitmap((imagedata*)arr[0],  31 + sin(t) * 30, 31 + sin(t) * 30);

    //Myrotater->rotateNscale((imagedata*)arr[0], mem, t, 60, 400, 400);

  

}



void Dxstuff::drawbitmap(byte* lmem, int w, int h, int inx, imagedata* idata,int px, int py,double tint) {

    
    int startx = 0;
    if (px < 0) startx = -px;

    int starty = 0;
    if (py < 0) starty = -py;

    int endx = idata->w;
    if ((px + idata->w) > w) endx = w - px;

    int endy = idata->h;
    if ((py + idata->h) > h) endy = h - py;


    for (int x = startx; x < endx; x++) {
        for (int y = starty; y < endy;  y++) {

            unsigned int ofs = (x + y * idata->w) * idata->ch;

            
            if (idata->data[ofs + 3] != 0) {

                int memofs = (px + x + (py + y) * w) * 4;

                lmem[memofs] =     (byte)(idata->data[ofs] * tint);
                lmem[memofs + 1] = (byte)(idata->data[ofs + 1]);
                lmem[memofs + 2] = (byte)(idata->data[ofs + 2]);

               // mainwindow->MyAnimationWindow->indexbuffer[(px + x + (py + y) * w)] = inx;


            }

//            if (MyFileLoader->ch == 4)
//                lmem[(px + x + (py + y) * w) * 4 + 3] = idata->data[ofs + 3];

           
           }


    }

};


void Dxstuff::loadallfiles(WCHAR* filelist) {

    WCHAR Fil[MAX_PATH];

    int l = lstrlenW(filelist) + 1;
    if (filelist[l + 1] == 0) {
        loadfile(filelist);
    }
    else {
        do {
            swprintf_s(Fil, lstrlenW(filelist) + lstrlenW(&filelist[l]) + 2, L"%s\\%s", filelist, &filelist[l]);
            loadfile(Fil);
            l += lstrlenW(&filelist[l]) + 1;
        } while (filelist[l + 1] != 0);
    }

    mainwindow->MyBrowser->find_number();

    mainwindow->MyBrowser->paintnow = true;

}







void Dxstuff::loadfile(WCHAR* filename) {


    

    imagedata* id = MyBMPLoader->loadfile(filename);

    
    if (id == 0) MessageBoxW(mainwindow->hWnd,L"Unable to load BMP",L"Error",MB_OK);

    if (id == nullptr) { return; }

    id->sw = 80;
    id->sh = 80;

    id->aspect = (double)id->w / id->h;

    id->id = (int)arr.size();

    arr.push_back(id);

}




void Dxstuff::drawbitmapscale(byte* lmem, int w, int h, int inx, imagedata* idata, int px, int py, double tint){



    int startx = 0;
    if (px < 0) startx = -px;

    int starty = 0;
    if (py < 0) starty = -py;

    int endx = idata->sw;
    if ((px + idata->sw) > w) endx = w - px;

    int endy = idata->sh;
    if ((py + idata->sh) > h) endy = h - py;


    double dx = (double)idata->w / (idata->sw + 1);
    double dy = (double)idata->h / (idata->sh + 1);


    double xx = startx * dx;


    for (int x = startx; x < endx; x++) {

        double yy = starty * dy;

        for (int y = starty; y < endy; y++) {

        
            byte* nd = avpix(idata, xx, yy, xx + dx, yy + dy);

            int memofs = (px + x + (py + y) * w) * 4;

            if (nd[3] != 0) {

                lmem[memofs] = (byte)(nd[0] * tint);
                lmem[memofs + 1] = nd[1];
                lmem[memofs + 2] = nd[2];


                //mainwindow->MyAnimationWindow->indexbuffer[(px + x + (py + y) * w)] = inx;


            }


            //if (MyFileLoader->ch == 4)
             //   lmem[(px + x + (py + y) * w) * 4 + 3] = nd[3];


            yy += dy;

        }

        xx += dx;

    }


}

void Dxstuff::drawbitmapscaleQuick(byte* lmem, int w, int h, int inx, imagedata* idata, int px, int py,double tint) {

    int startx = 0;
    if (px < 0) startx = -px;

    int starty = 0;
    if (py < 0) starty = -py;

    int endx = idata->sw;
    if ((px + idata->sw) > w) endx = w - px;

    int endy = idata->sh;
    if ((py + idata->sh) > h) endy = h - py;


    double dx = (double)idata->w / idata->sw;
    double dy = (double)idata->h / idata->sh;

    
    double xx = startx * dx + dx / 2.0;

    for (int x = startx; x < endx; x++) {
    
        double yy = starty * dy + dy / 2.0;
        
        for (int y = starty; y < endy; y++) {

            
            int ofs = (((int)xx + (int)yy * idata->w)) * idata->ch;

            if (idata->data[ofs + 3] != 0) {

                int memofs = (px + x + (py + y) * w) * 4;

                lmem[memofs] = (byte)(idata->data[ofs]*tint);
                lmem[memofs + 1] = idata->data[ofs + 1];
                lmem[memofs + 2] = idata->data[ofs + 2];

                //mainwindow->MyAnimationWindow->indexbuffer[(px + x + (py + y) * w)] = inx;

                //if (MyFileLoader->ch == 4)
                  //  lmem[(px + x + (py + y) * w) * 4 + 3] = idata->data[ofs+3];

            }

            yy += dy;
           

        }

        xx += dx;

    }


}


byte* Dxstuff::avpix(imagedata* id, double x1, double y1, double x2, double y2) {


        byte* pixelin = id->data;

        int ww = id->w;
        int hh = id->h;

        byte* r = (byte*)malloc(4);
        if (x1 > x2) { double tmpx = x1; x1 = x2; x1 = tmpx; }
        if (y1 > y2) { double tmpy = y1; y1 = y2; y1 = tmpy; }

        int cx1 = (int)ceil(x1);
        int cy1 = (int)ceil(y1);

        int fx1 = (int)floor(x1);
        int fy1 = (int)floor(y1);


        int cx2 = (int)ceil(x2);
        int cy2 = (int)ceil(y2);

        int fx2 = (int)floor(x2);
        int fy2 = (int)floor(y2);


        double sumr = 0.0;
        double sumg = 0.0;
        double sumb = 0.0;
        double suma = 0.0;



        if ((fx1 == fx2) && (fy1 == fy2)) {

            //alert("midt")

            int index = (fx1 + fy1 * ww) * id->ch;

            r[0] = (byte)pixelin[index];
            r[1] = (byte)pixelin[index+1];
            r[2] = (byte)pixelin[index+2];
            if (id->ch == 4)
                r[3] = (byte)pixelin[index+3];

            return r;

        }

        if ((fx1 == fx2) && (fy2 > fy1)) {

            //alert("h�g");

            for (int i = cy1; i < fy2; i++) {

                int index = (fx1 + i * ww) * id->ch;

                sumr += pixelin[index] * (x2 - x1);
                sumg += pixelin[index + 1] * (x2 - x1);
                sumb += pixelin[index + 2] * (x2 - x1);
                suma += pixelin[index + 3] * (x2 - x1);

            }

            //Topp
            int index = (fx1 + fy1 * ww) * id->ch;

            sumr += pixelin[index] * (cy1 - y1) * (x2 - x1);
            sumg += pixelin[index + 1] * (cy1 - y1) * (x2 - x1);
            sumb += pixelin[index + 2] * (cy1 - y1) * (x2 - x1);
            suma += pixelin[index + 3] * (cy1 - y1) * (x2 - x1);

            //Botn
            index = (fx1 + fy2 * ww) * id->ch;

            sumr += pixelin[index] * (y2 - fy2) * (x2 - x1);
            sumg += pixelin[index + 1] * (y2 - fy2) * (x2 - x1);
            sumb += pixelin[index + 2] * (y2 - fy2) * (x2 - x1);
            suma += pixelin[index + 3] * (y2 - fy2) * (x2 - x1);

            double d = (y2 - y1) * (x2 - x1);

            r[0] = (byte)(sumr / d);
            r[1] = (byte)(sumg / d);;
            r[2] = (byte)(sumb / d);;
            if (id->ch == 4)
                r[3] = (byte)(suma / d);

            return r;

        }

        if ((fy1 == fy2) && (fx2 > fx1)) {

            //alert("vid")

            for (int i = cx1; i < fx2; i++) {

                int index = (i + fy1 * ww) * id->ch;

                sumr += pixelin[index] * (y2 - y1);
                sumg += pixelin[index + 1] * (y2 - y1);
                sumb += pixelin[index + 2] * (y2 - y1);
                suma += pixelin[index + 3] * (y2 - y1);

            }

            //Venstre
            int index = (fx1 + fy1 * ww) * id->ch;

            sumr += pixelin[index] * (cx1 - x1) * (y2 - y1);
            sumg += pixelin[index + 1] * (cx1 - x1) * (y2 - y1);
            sumb += pixelin[index + 2] * (cx1 - x1) * (y2 - y1);
            suma += pixelin[index + 3] * (cx1 - x1) * (y2 - y1);


            //H�gre
            index = (fx2 + fy1 * ww) * id->ch;

            sumr += pixelin[index] * (x2 - fx2) * (y2 - y1);
            sumg += pixelin[index + 1] * (x2 - fx2) * (y2 - y1);
            sumb += pixelin[index + 2] * (x2 - fx2) * (y2 - y1);
            suma += pixelin[index + 3] * (x2 - fx2) * (y2 - y1);

            double d = (y2 - y1) * (x2 - x1);

            r[0] = (byte)(sumr / d);
            r[1] = (byte)(sumg / d);
            r[2] = (byte)(sumb / d);
            if (id->ch == 4)
                r[3] = (byte)(suma / d);

            return r;

        }


        //Stor
        
        for (int j = cy1; j < fy2; j++) {
            for (int i = cx1; i < fx2; i++) {

                int index = (i + j * ww) * id->ch;

                sumr += pixelin[index];
                sumg += pixelin[index + 1];
                sumb += pixelin[index + 2];
                suma += pixelin[index + 3];

            }
        }
        

        //venstre

        for (int j = cy1; j < fy2; j++) {

            int index = (fx1 + j * ww) * id->ch;

            sumr += pixelin[index] * (cx1 - x1);
            sumg += pixelin[index + 1] * (cx1 - x1);
            sumb += pixelin[index + 2] * (cx1 - x1);
            suma += pixelin[index + 3] * (cx1 - x1);

        }

        //H�gre

        for (int j = cy1; j < fy2; j++) {

            int index = (fx2 + j * ww) * id->ch;

            sumr += pixelin[index] * (x2 - fx2);
            sumg += pixelin[index + 1] * (x2 - fx2);
            sumb += pixelin[index + 2] * (x2 - fx2);
            suma += pixelin[index + 3] * (x2 - fx2);

        }

        //Topp

        for (int i = cx1; i < fx2; i++) {

            int index = (i + fy1 * ww) * id->ch;

            sumr += pixelin[index] * (cy1 - y1);
            sumg += pixelin[index + 1] * (cy1 - y1);
            sumb += pixelin[index + 2] * (cy1 - y1);
            suma += pixelin[index + 3] * (cy1 - y1);

        }

        //Botn

        for (int i = cx1; i < fx2; i++) {

            int index = (i + fy2 * ww) * id->ch;

            sumr += pixelin[index] * (y2 - fy2);
            sumg += pixelin[index + 1] * (y2 - fy2);
            sumb += pixelin[index + 2] * (y2 - fy2);
            suma += pixelin[index + 3] * (y2 - fy2);

        }



        //Topp venstre
        int index = (fx1 + fy1 * ww) * id->ch;

        sumr += pixelin[index] * (cx1 - x1) * (cy1 - y1);
        sumg += pixelin[index + 1] * (cx1 - x1) * (cy1 - y1);
        sumb += pixelin[index + 2] * (cx1 - x1) * (cy1 - y1);
        suma += pixelin[index + 3] * (cx1 - x1) * (cy1 - y1);

        //Topp h�gre
        index = (fx2 + fy1 * ww) * id->ch;

        sumr += pixelin[index] * (x2 - fx2) * (cy1 - y1);
        sumg += pixelin[index + 1] * (x2 - fx2) * (cy1 - y1);
        sumb += pixelin[index + 2] * (x2 - fx2) * (cy1 - y1);
        suma += pixelin[index + 3] * (x2 - fx2) * (cy1 - y1);


        //Botn venstre
        index = (fx1 + fy2 * ww) * id->ch;

        sumr += pixelin[index] * (cx1 - x1) * (y2 - fy2);
        sumg += pixelin[index + 1] * (cx1 - x1) * (y2 - fy2);
        sumb += pixelin[index + 2] * (cx1 - x1) * (y2 - fy2);
        suma += pixelin[index + 3] * (cx1 - x1) * (y2 - fy2);

        //Botn h�gre
        index = (fx2 + fy2 * ww) * id->ch;

        sumr += pixelin[index] * (x2 - fx2) * (y2 - fy2);
        sumg += pixelin[index + 1] * (x2 - fx2) * (y2 - fy2);
        sumb += pixelin[index + 2] * (x2 - fx2) * (y2 - fy2);
        suma += pixelin[index + 3] * (x2 - fx2) * (y2 - fy2);



        double d = (y2 - y1) * (x2 - x1);

       
        r[0] = (byte)((double)(sumr / d));
        r[1] = (byte)((double)(sumg / d));
        r[2] = (byte)((double)(sumb / d));
        if (id->ch == 4) 
            r[3] = (byte)((double)(suma / d));

        return r;



}