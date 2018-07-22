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
    //A method to calculate the number of iterations for each pixel.
    void calculateIterations();
    void drawFractal();
    void writeBitmap(std::string name);
    // This method calculates the number of pixels which fall in a certain range
    void calculateRangeTotals();
    int getRange(int iterations) const;

    int width_;
    int height_;
    bool gotFirstRange_{false};

    Bitmap bitmap_;
    ZoomList zoomlist_;

    std::vector<int> ranges_;
    std::vector<RGB> colors_;
    std::vector<int> rangesTotal_;

    //histogram_ stores the number of pixels with a particula number of iterations
    std::unique_ptr<int[]> histogram_;

    std::unique_ptr<int[]> fractal_;

public:
    FractalCreator(int width, int height, double scale);
    void addCenterShift(const Zoom &zoom);
    void run(std::string name);
    void addRange(double rangeEndIteration, const RGB &rgb);
    ~FractalCreator();
};

