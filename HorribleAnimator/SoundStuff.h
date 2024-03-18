#pragma once

class MainWindow;

class SoundStuff
{
public:

	SoundStuff(MainWindow* _mainwindow);

	void initDx();

	void load(WCHAR* filename);
	void save_wav(WCHAR* filename);

	void play(int t);
	void stop();
	void reset();
	void freeall();

	MainWindow* mainwindow;


	WAVEFORMATEX ppFormat;

	CHAR riff[5] = "RIFF";

	wavinfo* info;
	
	std::vector< SoundCardInfo* > soundCardList;


	IMMDeviceEnumerator* deviceEnumerator;
	IMMDevice* audioDevice;
	IAudioRenderClient* audioRenderClient;
	IAudioClient2* audioClient;

	UINT32 bufferSizeInFrames;
	
	WAVEFORMATEX mixFormat = {};

	int soundpos;


	int data_size;

	INT16* data;

	int size;
	
	WCHAR LydFilNamn[100] = L"vits.wav";


};

