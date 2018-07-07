#pragma once

#include <string>
#include<cstdint>
#include<memory>

class Bitmap
{
public:
    Bitmap(int width, int height);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    bool write(std::string fileName);
    ~Bitmap();

private:
    int width_{0};
    int height_{0};
    std::unique_ptr<uint8_t[]> pPixels_{nullptr};
};

