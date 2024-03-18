#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstddef>


#pragma pack(push, 1)
typedef struct {
    uint16_t signature;     // Signature ('BM')
    uint32_t fileSize;      // File size
    uint16_t reserved1;     // Reserved (0)
    uint16_t reserved2;     // Reserved (0)
    uint32_t dataOffset;    // Data offset to the start of image data
    uint32_t headerSize;    // Size of this header (40 bytes)
    int32_t width;          // Image width
    int32_t height;         // Image height
    uint16_t planes;        // Number of color planes (must be 1)
    uint16_t bitDepth;      // Bits per pixel
    uint32_t compression;   // Compression method (0 for uncompressed)
    uint32_t imageSize;     // Image size (may be 0 for uncompressed)
    int32_t xPixelsPerM;    // Horizontal resolution (pixels per meter)
    int32_t yPixelsPerM;    // Vertical resolution (pixels per meter)
    uint32_t colorsUsed;    // Number of colors in the palette
    uint32_t colorsImportant; // Number of important colors used
} BMPHeader;
#pragma pack(pop)

class BMPLoader {

public:

	BMPLoader();

    imagedata* loadfile(WCHAR* filename);

};
