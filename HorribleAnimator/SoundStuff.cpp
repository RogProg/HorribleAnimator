
#include "framework.h"
#include "SoundStuff.h"

SoundStuff::SoundStuff(MainWindow* _mainwindow) {

	mainwindow = _mainwindow;

    soundpos = 0;

    data = NULL;

    data_size = 0;

	initDx();


}



void SoundStuff::initDx() {

    HRESULT hr = CoInitializeEx(nullptr, COINIT_SPEED_OVER_MEMORY);
    assert(hr == S_OK);

    
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (LPVOID*)(&deviceEnumerator));
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to create Instance", L"Error", MB_OK);

        return;
    }

    
    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &audioDevice);
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to get endpoint", L"Error", MB_OK);

        return;
    }

    deviceEnumerator->Release();

    
    hr = audioDevice->Activate(__uuidof(IAudioClient2), CLSCTX_ALL, nullptr, (LPVOID*)(&audioClient));
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to activate sound", L"Error", MB_OK);

        return;
    }


    audioDevice->Release();

    // WAVEFORMATEX* defaultMixFormat = NULL;
    // hr = audioClient->GetMixFormat(&defaultMixFormat);
    // assert(hr == S_OK);

    
    mixFormat.wFormatTag = WAVE_FORMAT_PCM;
    mixFormat.nChannels = 2;
    mixFormat.nSamplesPerSec = 44100;//defaultMixFormat->nSamplesPerSec;
    mixFormat.wBitsPerSample = 16;
    mixFormat.nBlockAlign = (mixFormat.nChannels * mixFormat.wBitsPerSample) / 8;
    mixFormat.nAvgBytesPerSec = mixFormat.nSamplesPerSec * mixFormat.nBlockAlign;

    const INT64 REFTIMES_PER_SEC = 10000000; // hundred nanoseconds
    REFERENCE_TIME requestedSoundBufferDuration = REFTIMES_PER_SEC * 2;
    DWORD initStreamFlags = (AUDCLNT_STREAMFLAGS_RATEADJUST
        | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM
        | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY);
    hr = audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED,
        initStreamFlags,
        requestedSoundBufferDuration,
        0, &mixFormat, nullptr);

    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to init stream", L"Error", MB_OK);

        return;
    }


    
    hr = audioClient->GetService(__uuidof(IAudioRenderClient), (LPVOID*)(&audioRenderClient));
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to get service", L"Error", MB_OK);

        return;
    }


    
    hr = audioClient->GetBufferSize(&bufferSizeInFrames);
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to get buffersize", L"Error", MB_OK);

        return;
    }


    hr = audioClient->Start();
    if (hr != S_OK) {

        MessageBoxW(mainwindow->hWnd, L"Unable to start audio client", L"Error", MB_OK);

        return;
    }





	
	WCHAR DIR[MAX_PATH];

	GetCurrentDirectoryW(MAX_PATH, DIR);

	//swprintf_s(Fil, lstrlenW(DIR) + lstrlenW(LydFilNamn) + 2, L"%s\\%s", DIR, LydFilNamn);

	//load(Fil);




	
	
	

}

void SoundStuff::play(int t) {


    if (data == NULL) return;
	
   // while (true)
   // {
        // Padding is how much valid data is queued up in the sound buffer
        // if there's enough padding then we could skip writing more data
        UINT32 bufferPadding;
        HRESULT hr = audioClient->GetCurrentPadding(&bufferPadding);
        if (hr != S_OK) {

            MessageBoxW(mainwindow->hWnd, L"Unable to get padding", L"Error", MB_OK);

            return;
        }
        // How much of our sound buffer we want to fill on each update.
        // Needs to be enough so that the playback doesn't reach garbage data
        // but we get less latency the lower it is (e.g. how long does it take
        // between pressing jump and hearing the sound effect)
        // Try setting this to e.g. bufferSizeInFrames / 250 to hear what happens when
        // we're not writing enough data to stay ahead of playback!
        UINT32 soundBufferLatency = bufferSizeInFrames / 50;
        UINT32 numFramesToWrite = soundBufferLatency - bufferPadding;

        INT16* buffer;
        hr = audioRenderClient->GetBuffer(numFramesToWrite, (BYTE**)(&buffer));
        assert(hr == S_OK);

        for (UINT32 frameIndex = 0; frameIndex < numFramesToWrite; ++frameIndex)
        {

            if (soundpos < size) {

                *buffer++ = data[soundpos]; // left
                *buffer++ = data[soundpos + 1]; // right

                soundpos += 2;
            }
            else {

                *buffer++ = 0;
                *buffer++ = 0;

            }
        }
        hr = audioRenderClient->ReleaseBuffer(numFramesToWrite, 0);
        if (hr != S_OK) {

            MessageBoxW(mainwindow->hWnd, L"Unable to release buffer", L"Error", MB_OK);

            return;
        }


   

}


void SoundStuff::stop() {

    mainwindow->MyAnimationWindow->play = false;

}

void SoundStuff::reset() {

	


}

void SoundStuff::freeall() {

    audioClient->Stop();
    audioClient->Release();
    audioRenderClient->Release();
}


void SoundStuff::load(WCHAR* filename) {

	FILE* fp = NULL;

	_wfopen_s(&fp, filename, L"rb");
	if (fp) {

        info = new wavinfo();
    
        fread(info,1,sizeof(wavinfo),fp);


            data_size = info->data_size;

 			size = data_size / sizeof(short);
    		data = (short*)malloc(data_size);

            

			fread(data, sizeof(short), size, fp);


    }

    fclose(fp);

}



void SoundStuff::save_wav(WCHAR* filename) {

	FILE* fp = NULL;


	_wfopen_s(&fp, filename, L"wb");
	
     if (fp) {

        fwrite(info,sizeof(wavinfo),1,fp);
		
	    fwrite(data, sizeof(short) , size, fp);

     }

     fclose(fp);

}