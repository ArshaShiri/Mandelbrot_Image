#pragma once

#include <cstdint>

#pragma pack(2)

struct BitmapFileHeader
{
    char header[2]{'B','M'};
    int32_t fileSize;   //due to the fact that the bitmap has a fixed format
    int32_t reserved{0};
    int32_t dataOffset;
};