
#include "framework.h"

#include "BMPLoader.h"





BMPLoader::BMPLoader() {



}

imagedata* BMPLoader::loadfile(WCHAR* filename) {

    imagedata* imagedatatmp = new imagedata;

	FILE* pFile;

	_wfopen_s(&pFile, filename, L"rb");

    if (pFile == NULL) {
        printf("Error: Unable to open file.\n");
        return NULL;
    }

   
    

    BMPHeader header;
    fread(&header, sizeof(header), 1, pFile);

    if (header.signature != 0x4D42) {
        printf("Error: Not a BMP file.\n");
        fclose(pFile);
        return NULL;
    }
    

    int dataSize = header.width * header.height * (header.bitDepth / 8);
    imagedatatmp->data = (unsigned char*)malloc(dataSize);


    fseek(pFile, header.dataOffset, SEEK_SET);


    fread(imagedatatmp->data, dataSize, 1, pFile);


    if (header.bitDepth != 32) return NULL;


    imagedatatmp->w = header.width;
    imagedatatmp->h = header.height;

    imagedatatmp->ch = 4;

    fclose(pFile);

    return imagedatatmp;

}