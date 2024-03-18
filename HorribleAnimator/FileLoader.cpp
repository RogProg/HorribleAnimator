
#include "framework.h"



#include "FileLoader.h"




unsigned DLL_CALLCONV
myReadProc(void* buffer, unsigned size, unsigned count, fi_handle handle) {
	return (unsigned int)fread(buffer, (size_t)size, (size_t)count, (FILE*)handle);
}

unsigned DLL_CALLCONV
myWriteProc(void* buffer, unsigned size, unsigned count, fi_handle handle) {
	return (unsigned int)fwrite(buffer, (size_t)size, (size_t)count, (FILE*)handle);
}

int DLL_CALLCONV
mySeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE*)handle, offset, origin);
}

long DLL_CALLCONV
myTellProc(fi_handle handle) {
	return ftell((FILE*)handle);
}

FileLoader::FileLoader() {

	

	io.read_proc = myReadProc;
	io.write_proc = myWriteProc;
	io.seek_proc = mySeekProc;
	io.tell_proc = myTellProc;


}



FileLoader::~FileLoader() {



}

imagedata* FileLoader::loadfile(WCHAR* filename) {

		imagedata* imagedatatmp = new imagedata;

		mem = nullptr;
	
		//size_t i;

		//CHAR* cfilename = (CHAR*)malloc(wcslen(filename));
//		wcstombs_s(&i,cfilename, wcslen(filename) , filename, wcslen(filename)-1);



		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		fif = FreeImage_GetFileTypeU(filename, 0);
		// if still unknown, try to guess the file format from the file extension
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilenameU(filename);
		// if still unkown, return failure
		if (fif == FIF_UNKNOWN)
			return nullptr;

		FIBITMAP* dib = nullptr;

		// check that the plugin has reading capabilities and load the file
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_LoadU(fif, filename);
		// if the image failed to load, return failure
		if (!dib)
			return nullptr;

		if (fif != FIF_UNKNOWN) {

			// load from the file handle
			FIBITMAP* dib = dib = FreeImage_LoadU(fif, filename); //FreeImage_LoadFromHandle(fif, &io, (fi_handle)file, 0);

			imagedatatmp->w = FreeImage_GetWidth(dib);
			imagedatatmp->h = FreeImage_GetHeight(dib);

			
			/*
			int  m_bpp = FreeImage_GetBPP(dib);
			
			
			if (m_bpp == 8)
				imagedatatmp->ch = 1;
			else if (m_bpp == 24)
				imagedatatmp->ch = 3;
			else if (m_bpp == 32)
				*/


			FreeImage_FlipVertical(dib);

			FIBITMAP* dib32 = FreeImage_ConvertTo32Bits(dib);
			
			imagedatatmp->ch = 4;
		
		    imagedatatmp->data  = FreeImage_GetBits(dib32);
			
			FreeImage_Unload(dib);

			return imagedatatmp;

	}
	
		return nullptr;

}