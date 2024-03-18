// HorribleAnimator.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HorribleAnimator.h"

extern "C" {

    int initencoder(char* filename, int inwidth, int inheight, int inwavlength);
    bool encodeframe(int16_t* inaudio, char* invideo);
    void encoderclose();

}



#define MAX_LOADSTRING 100

 

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

MainWindow* MyMainWindow;

WCHAR currdir[MAX_PATH];
WCHAR saveproj[MAX_PATH];

HMENU hmenu;

RECT rcClient;  // Client area of parent window.
int cyVScroll;  // Height of scroll bar arrow.
HWND hwndPB;    // Handle of progress bar.



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)


{



    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HORRIBLEANIMATOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HORRIBLEANIMATOR_ACCEL));

    //MSG msg;

    
    EnableMenuItem(hmenu, ID_FILE_SAVEPROJ32788, MF_GRAYED);

    MSG message = { 0 };
    // Main message loop:
    //while (GetMessage(&msg, nullptr, 0, 0))
    
    int starttime = timeGetTime();

    while (message.message != WM_QUIT)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else {

            if ((timeGetTime() - starttime) > 1000.0 / 25.0) {

                starttime = timeGetTime();

                if (MyMainWindow->MyAnimationWindow->play) {
                    MyMainWindow->MySoundStuff->play(0);
                }

                MyMainWindow->paint();
                MyMainWindow->drawit();

                int usedtime = timeGetTime() - starttime;

                MyMainWindow->MyObjectWindow->load = (usedtime *  25.0 / 10000.0);



            }
            


        }
    }

    return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HORRIBLEANIMATOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HORRIBLEANIMATOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable



   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   RECT rc;
   GetWindowRect(hWnd, &rc);

   D2D1_SIZE_U size;

   size = D2D1::SizeU( rc.right - rc.left,  rc.bottom - rc.top);

   MyMainWindow = new MainWindow(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   hmenu = GetMenu(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {

    case WM_SIZE:
    {


        MyMainWindow->resize();

        break;

    }

    case WM_RBUTTONDOWN:
    {


        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        MyMainWindow->mouseRclick(xPos, yPos);

        break;


    }


    case WM_LBUTTONDOWN:
    {


       

        //MessageBox(hWnd, L"Mus", L"Sus", MB_OK);

        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        MyMainWindow->mouseclick(xPos, yPos);

        break;

    }

    case WM_LBUTTONUP:
    {

        //MessageBox(hWnd, L"Mus", L"Sus", MB_OK);

        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        MyMainWindow->mouseup(xPos, yPos);

        break;

    }

    case WM_RBUTTONUP:
    {

        //MessageBox(hWnd, L"Mus", L"Sus", MB_OK);

        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        MyMainWindow->mouseRup(xPos, yPos);

        break;

    }

    case WM_MOUSEMOVE:
    {

        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);

        MyMainWindow->mousemove(xPos,yPos);

        break;

    }


    case WM_CREATE:

        

        break;


    case WM_KEYDOWN:
    {


        // Parse the menu selections:
        switch (wParam)
        {


        case 'Z':
            if (GetAsyncKeyState(VK_CONTROL)) {
                
                MyMainWindow->MyUndoClass->restore_last();

            }
            break;

        }

        if (wParam == VK_INSERT) {

            MyMainWindow->MyAnimationWindow->MyDataObject->insert(MyMainWindow->MyTimeBar->slider);

        }
        /*
        if (wParam == VK_DELETE) {

            MyMainWindow->MyAnimationWindow->MyDataObject->remove(MyMainWindow->MyTimeBar->slider);

        }
        */

        if (wParam == VK_MULTIPLY) {

            MyMainWindow->MyAnimationWindow->menuselect = MyMainWindow->MyAnimationWindow->selected;

            MyMainWindow->MyAnimationWindow->setCue();


        }



        if (wParam == VK_DELETE) {

            MyMainWindow->MyAnimationWindow->MyDataObject->deleteCuePoint(MyMainWindow->MyTimeBar->slider,MyMainWindow->MyAnimationWindow->selected);

            MyMainWindow->MyAnimationWindow->MyDataObject->update(MyMainWindow->MyTimeBar->slider);

        }


        if (wParam == VK_SPACE) {

            if (!MyMainWindow->MyAnimationWindow->play) {

                if (MyMainWindow->MyTimeBar->endpoint == 0) {

                    MessageBox(MyMainWindow->hWnd, L"Set endpoint or load Wav file!", L"Warning!", MB_OK);
                    
                    break;

                }

                MyMainWindow->MyAnimationWindow->play = true;   

		        MyMainWindow->MySoundStuff->soundpos = 2 * 44100 / 25 * MyMainWindow->MyTimeBar->slider;

            } else {

                MyMainWindow->MyAnimationWindow->play = false;

		        MyMainWindow->MySoundStuff->stop();

            }

        }


        if (wParam == VK_RETURN) {

            MyMainWindow->MyAnimationWindow->menuselect = MyMainWindow->MyAnimationWindow->selected;

            MyMainWindow->MyAnimationWindow->showImageChanger();

        }

        if (wParam == VK_LEFT) {

            MyMainWindow->MyAnimationWindow->move_cue_left();

        }

        if (wParam == VK_RIGHT) {

            MyMainWindow->MyAnimationWindow->move_cue_right();

        }


        if (wParam == VK_UP) {

            MyMainWindow->MyAnimationWindow->gotoNextCue();

        }

        if (wParam == VK_DOWN) {

            MyMainWindow->MyAnimationWindow->gotoPrevCue();

        }

        if (wParam == VK_ADD) {

            if (!MyMainWindow->MyAnimationWindow->is_active())
                MyMainWindow->MyTimeBar->frame_right();

            break;

        }

        if (wParam == VK_SUBTRACT) {

            MyMainWindow->MyTimeBar->frame_left();

            break;

        }
    }



    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {


            case 'z':
                if (GetAsyncKeyState(VK_CONTROL)) {
                    MessageBox(hWnd, L"control - z",L"Jalla",MB_OK);
                }
                break;

            case ID_SCENE_GOTOPREVSCENE: {

                MyMainWindow->MyAnimationWindow->gotoPrevScene();



                break;
            }


            case ID_SCENE_GOTONEXTSCENE: {

                MyMainWindow->MyAnimationWindow->gotoNextScene();

                break;

            }

            case ID_SCENE_SETENDPOINT: {


                MyMainWindow->MyTimeBar->endpoint = MyMainWindow->MyTimeBar->slider;

                break;

            }

            case ID_Menu32781:
            {

                OPENFILENAMEW ofn;
                WCHAR szFileName[MAX_PATH] = L"";

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"Wavfile\0*.wav\0\0";
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                ofn.lpstrDefExt = L"wav";
                ofn.lpstrInitialDir = currdir;

                if (GetOpenFileNameW(&ofn))
                {

                    

                    MyMainWindow->MySoundStuff->load(ofn.lpstrFile);

                    MyMainWindow->MyTimeBar->endpoint = (int)((float)MyMainWindow->MySoundStuff->size / (2.0 * 44100.0) * 25.0);


                }

                break;

            }


            case ID_FILE_OPEN:
            {

                //MessageBox(hWnd, L"File", L"File", MB_OK);
                OPENFILENAMEW ofn;
                WCHAR szFileName[MAX_PATH] = L"";

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"BMPs\0*.bmp\0\0";
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT;
                ofn.lpstrDefExt = L"bmp";
                ofn.lpstrInitialDir = currdir;

                if (GetOpenFileNameW(&ofn))
                {

                    MyMainWindow->MyDxstuff->loadallfiles(ofn.lpstrFile);

                }

                break;
            }
            
            case ID_FILE_SAVEPROJ:
            {

                OPENFILENAMEW ofn;
                WCHAR szFileName[MAX_PATH] = L"";

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"Horrible\0*.han\0\0";
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_EXPLORER  | OFN_HIDEREADONLY;
                ofn.lpstrDefExt = L"awa";
                ofn.lpstrInitialDir = currdir;

                

                if (GetSaveFileNameW(&ofn))
                {

                    EnableMenuItem(hmenu, ID_FILE_SAVEPROJ32788, MF_ENABLED);

                    wcsncpy_s(saveproj, MAX_PATH, ofn.lpstrFile, wcslen(ofn.lpstrFile));


                    MyMainWindow->MyAnimationWindow->MyDataObject->SaveAll(ofn.lpstrFile);
                    
                }

                break;
            }

            case ID_FILE_SAVEPROJ32788:
            {
                MyMainWindow->MyAnimationWindow->MyDataObject->SaveAll(saveproj);

                break;

            }


            case ID_FILE_OPENPROJ:
            {

                OPENFILENAMEW ofn;
                WCHAR szFileName[MAX_PATH] = L"";

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"Horrible\0*.han\0\0";
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                ofn.lpstrDefExt = L"txt";
                ofn.lpstrInitialDir = currdir;

                if (GetOpenFileNameW(&ofn))
                {

                    wcsncpy_s(saveproj, MAX_PATH, ofn.lpstrFile, wcslen(ofn.lpstrFile));

                    EnableMenuItem(hmenu, ID_FILE_SAVEPROJ32788, MF_ENABLED);

                    MyMainWindow->MyAnimationWindow->MyDataObject->LoadAll(ofn.lpstrFile);

                    MyMainWindow->MyTimeBar->slider = 0;
                    MyMainWindow->MyTimeBar->offset = 0;

                    MyMainWindow->MyAnimationWindow->MyDataObject->update(0);


                    MyMainWindow->MyBrowser->paintnow = true;

                }

                break;


            }

            case ID_FILE_EXPORT:
            {



                CHAR dir[MAX_PATH];
                GetCurrentDirectoryA(MAX_PATH,dir);
                
              

                OPENFILENAMEW ofn;
                WCHAR szFileName[MAX_PATH] = L"";

                ZeroMemory(&ofn, sizeof(ofn));

                ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
                ofn.hwndOwner = hWnd;
                ofn.lpstrFilter = L"(*.mpeg)\0";
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
                ofn.lpstrDefExt = L"txt";
                ofn.lpstrInitialDir = currdir;

                if (GetOpenFileNameW(&ofn))
                {


                    CHAR fil[MAX_PATH];
                    

                    wcstombs_s(NULL, fil, wcslen(ofn.lpstrFile) + 1, ofn.lpstrFile, wcslen(ofn.lpstrFile) + 1);

                    DeleteFileA(fil);


                        initencoder(fil, 1280, 720,MyMainWindow->MySoundStuff->size);

                        GetClientRect(hWnd, &rcClient);

                        cyVScroll = GetSystemMetrics(SM_CYVSCROLL);

                        hwndPB = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR)NULL,
                            WS_CHILD | WS_VISIBLE, rcClient.left,
                            rcClient.bottom - cyVScroll,
                            rcClient.right, cyVScroll,
                            hWnd, (HMENU)0, hInst, NULL);


                        SendMessage(hwndPB, PBM_SETRANGE, 0, MAKELPARAM(0, MyMainWindow->MyTimeBar->endpoint));

                        SendMessage(hwndPB, PBM_SETSTEP, (WPARAM)1, 0);

                    


                    MyMainWindow->MyAnimationWindow->resize(200, 0, 1280, 720);

                   


                    int imgsize = MyMainWindow->MyAnimationWindow->vieww * MyMainWindow->MyAnimationWindow->viewh * 3;

                    byte* tmpdata = (byte*)malloc(imgsize);

                    MyMainWindow->MyAnimationWindow->selected = -1;

                    int slider = 0;

                    
                    for (int t = 0; t < MyMainWindow->MyTimeBar->endpoint; t++) {


                        MyMainWindow->MyAnimationWindow->MyDataObject->update(slider);
                        MyMainWindow->MyAnimationWindow->paint();


                        int xxx = MyMainWindow->MyAnimationWindow->boxx1;

                        for (int xx = 0; xx < MyMainWindow->MyAnimationWindow->vieww; xx++) {

                            int yyy = MyMainWindow->MyAnimationWindow->boxy1;

                            for (int yy = 0; yy < MyMainWindow->MyAnimationWindow->viewh; yy++) {

                                int ofs2 = (xx + yy * MyMainWindow->MyAnimationWindow->vieww) * 3;
                                int ofs1 = (xxx + yyy * MyMainWindow->MyAnimationWindow->w) * 4;

                                tmpdata[ofs2] = MyMainWindow->MyAnimationWindow->lmem[ofs1 + 2];
                                tmpdata[ofs2 + 1] = MyMainWindow->MyAnimationWindow->lmem[ofs1 + 1];
                                tmpdata[ofs2 + 2] = MyMainWindow->MyAnimationWindow->lmem[ofs1];

                                yyy++;

                            }

                            xxx++;

                        }



                        int16_t* indata = (int16_t*)MyMainWindow->MySoundStuff->data;




                        while (!encodeframe(indata, (char*)tmpdata));

                        slider++;

                        SendMessage(hwndPB, PBM_STEPIT, 0, 0);

                    }

                    free(tmpdata);

                    encoderclose();

                   

                    MyMainWindow->resize();

         

                    printf("done!");

                    DestroyWindow(hwndPB);

                    
                }

                break;

            }


            case ID_SCENE_SELECTBACKGROUND: 
            {


                MyMainWindow->MyAnimationWindow->selectBackground();

                break;
            }

            case ID_SCENE_NEWSCENE:
            {

                MyMainWindow->MyAnimationWindow->newScene(MyMainWindow->MyTimeBar->slider);

                break;
            }
            

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);


            

        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
