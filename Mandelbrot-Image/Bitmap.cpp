#include<fstream>

#include "Bitmap.h"
#include "BitmapFile.h"
#include "BitmapInfo.h"

using namespace std;

//Every pixel has 3 bytes (3 uint8_t)
Bitmap::Bitmap(int width, int height) :
    width_{width}, height_{height}, pPixels_{new uint8_t[width * height *3]{0}}
{}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t *pPixel = pPixels_.get(); //1 byte of info for each red or blue or green
    pPixel += 3 * y * width_ + 3 * x; //each pixel takes 3 bytes

    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;

}

bool Bitmap::write(string fileName)
{
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + width_ * height_ * 3;
    // size from the begining of the file to where the data starts
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);
    infoHeader.width = width_;
    infoHeader.height = height_;
    ofstream file;
    file.open(fileName, ios::out | ios::binary);

    if (!file)
    {
        return false;
    }
    file.write((char *)&fileHeader, sizeof(fileHeader));
    file.write((char *)&infoHeader, sizeof(infoHeader));
    file.write((char *)pPixels_.get(), width_ * height_ * 3); //get() gives the raw pointer 
    file.close();
    if (!file)
    {
        return false;
    }
    return true;
}


Bitmap::~Bitmap()
{}
