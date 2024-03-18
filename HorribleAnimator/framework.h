// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers





// Windows Header Files
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <CommCtrl.h>
#include <timeapi.h>
#include <commdlg.h>
#include <shellapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>
#include <winnt.h>
#include <winbase.h>
#include <vector>
#include <math.h>
#include <commdlg.h>
#include <iostream>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <cwchar>


#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <mmeapi.h>

#include <mmdeviceapi.h>
#include <audioclient.h>


extern "C" {
#include <libavutil/avassert.h>
#include <libavutil/channel_layout.h>
#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>

}


struct wavinfo {
    
    char riff_header[4]; 
    int wav_size; 
    char wave_header[4];
 
    char fmt_header[4];
    int fmt_chunk_size;
    short audio_format;
    short num_channels;
    int sample_rate;
    int byte_rate;
    short sample_alignment;
    short bit_depth;
 
    char data_header[4];
    int data_size;
    
};
 

struct SoundCardInfo
{
	LPGUID lpGuid;
	WCHAR description[100];
};


struct testdata {

	int a, b, c;

};

struct posdata {

	int ofsx, ofsy;

};

struct imagedata {

    bool visible;

	int time;

	int w, h, ch;
		
	double x, y;

	int sw, sh;

	double ofsx, ofsy;

	double rotposx, rotposy;

	double angle;

	double size,ownsize;

	double tmpw;

	int id;

	double aspect;

	int layer;

	int parent;
	
	int imagelink;

	int scene;
    
    byte* data;

};


struct UndoInfo
{

    int time;
    int id;

    int type;

    int cuenr1;

    int cuenr2;

    int img;

    int link;

    imagedata* data;
    imagedata* olddata;

};


struct textdata {

	WCHAR text[40];

	int x, y;

	int sender;

};



const int OBJECTWINSENDER = 1;
const int AINIMATIONWINDOWSENDER = 2;
const int NEWBACKGROUNDSENDER = 3;
const int BROWSERSENDER = 4;


#include <cstdint>

#include "Encoder.h"

#include "BMPLoader.h"

#include "GfxTools.h"

#include "Dxstuff.h"

#include "Rotater.h"

#include "DataObject.h"

#include "GfxTools.h"

#include "SoundStuff.h"

#include "BaseWindow.h"

#include "Message.h"

#include "ImageChanger.h"

#include "Floater.h"

#include "Menu.h"

#include "Browser.h"

#include "timebar.h"

#include "ObjectWindow.h"

#include "AnimationWindow.h"

#include "UndoClass.h"

#include "MainWindow.h"

