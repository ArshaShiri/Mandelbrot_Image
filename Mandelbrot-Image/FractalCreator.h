#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include "ZoomList.h"

class FractalCreator
{
private:
    void calculateIterations();
    void calculateTotalIterations();
    void drawFractal();
    void writeBitmap(std::string name);
    void calculateRangeTotals();
    int getRange(int iterations) const;
    bool gotFirstRange{ false };

    int width_;
    int height_;
    int total_;

    Bitmap bitmap_;
    ZoomList zoomlist_;

    std::vector<int> ranges_;
    std::vector<RGB> colors_;
    std::vector<int> rangesTotal_;
    //histogram_ stores the number of pixels with a particula number of iterations
    std::unique_ptr<int[]> histogram_;
    std::unique_ptr<int[]> fractal_;

public:
    FractalCreator(int width, int height);
    void addZoom(const Zoom &zoom);
    void run(std::string name);
    void addRange(double rangeEndIteration, const RGB &rgb);
    ~FractalCreator();
};

