
#pragma once

class MainWindow;

template<class Interface>
inline void SafeRelease(
    Interface** ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();
        (*ppInterfaceToRelease) = NULL;
    }
}

class Dxstuff
{

public:

	Dxstuff(HWND _hWnd,MainWindow* _mainwindow);
	~Dxstuff();

    void createDevices();
    

    void addtext(WCHAR* txt, int _x, int _y);

    void paint(double t);

    

    void drawbitmap(byte* lmem,int w,int h,int inx, imagedata* idata, int px, int py, double tint);
    
    void loadallfiles(WCHAR* filelist);
    void loadfile(WCHAR* filename);

    void drawbitmapscale(byte* lmem, int w, int h, int inx, imagedata* idata, int px, int py, double tint);
    void drawbitmapscaleQuick(byte* lmem, int w, int h, int inx, imagedata* idata, int px, int py,  double tint);


    byte* avpix(imagedata* id, double x1, double y1, double x2, double y2);

//private:
	
    HWND hWnd;

    MainWindow* mainwindow;
	
    ID2D1Factory* m_pDirect2dFactory = NULL;
    IDWriteTextFormat* m_pTextFormat;
    IDWriteTextFormat* m_pTextFormatTime;
    ID2D1SolidColorBrush* m_pD2DBrush;
    IDWriteFactory* pDWriteFactory;
    ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
    ID2D1Bitmap* pBitmap;

    GfxTools* MyGfxTools;

    D2D1_SIZE_U size;
    


    WCHAR DIR[MAX_PATH];
    WCHAR Fil[MAX_PATH];
   
    


   
   // byte* mem;


//    FileLoader* MyFileLoader;

    BMPLoader* MyBMPLoader;

    //Browser* MyBrowser;

    //Rotater* Myrotater;

    std::vector< imagedata* > arr;

    

    int w;


    WCHAR controlfile[20] = L"control.bmp";
    WCHAR okfile[20] = L"ok.bmp";
    WCHAR up[20] = L"up.bmp";
    WCHAR down[20] = L"down.bmp";
    
    
    imagedata* controlimg;
    imagedata* upimg;
    imagedata* downimg;
    imagedata* okimg;

};

