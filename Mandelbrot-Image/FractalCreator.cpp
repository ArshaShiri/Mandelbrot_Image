#include "FractalCreator.h"
#include <iostream>
#include <assert.h>

FractalCreator::FractalCreator(int width, int height, double scale) :
    width_(width),
    height_(height),
    histogram_(new int[Mandelbrot::MAX_ITERATIONS]()),
    fractal_(new int[width_ * height_]()),
    bitmap_(width, height),
    zoomlist_(width, height)
{
    zoomlist_.updateDataCenter(Zoom(width /2 , height / 2, scale));
}

void FractalCreator::run(std::string name)
{
    calculateIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap(name);
}

void FractalCreator::calculateIterations()
{
    for (auto y = 0; y < height_; y++)
    {
        for (auto x = 0; x < width_; x++)
        {
            std::pair<double, double> coords = zoomlist_.getCoordinates(x, y);

            int iterations = Mandelbrot::getNumberOfIterations(coords.first, coords.second);
            fractal_[y * width_ + x] = iterations;
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                histogram_[iterations]++;
            }
        }
    }
}

void FractalCreator::addRange(double rangeEndIteration, const RGB &rgb)
{
    ranges_.push_back(rangeEndIteration * Mandelbrot::MAX_ITERATIONS);
    colors_.push_back(rgb);

    if (gotFirstRange_)
    {
        rangesTotal_.push_back(0);
    }
    gotFirstRange_ = true;
}

void FractalCreator::calculateRangeTotals()
{
    int rangeIndex = 0;
    for (auto i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        int numberOfPixels = histogram_[i];
        if (i >= ranges_[rangeIndex + 1])
            rangeIndex++;
        rangesTotal_[rangeIndex] += numberOfPixels;
    }
    for (int value : rangesTotal_)
    {
        std::cout << value << std::endl;
    }
}

void FractalCreator::drawFractal()
{
    for (double y = 0; y < height_; y++)
    {
        for (double x = 0; x < width_; x++)
        {
            int iterations = fractal_[y * width_ + x];
            int range = getRange(iterations);
            int rangeTotal = rangesTotal_[range];
            int rangeStart = ranges_[range];
            RGB &startColor = colors_[range];
            RGB &endColor = colors_[range+1];
            RGB colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                int totalPixels = 0;
                //totalPixels = histogram_[iterations];
                for (auto i = rangeStart; i <= iterations; i++)
                {
                    totalPixels += histogram_[i];
                }
                red = startColor.red_ + colorDiff.red_ * pow((double)totalPixels / rangeTotal, 1);
                green = startColor.green_ + colorDiff.green_ * pow((double)totalPixels / rangeTotal, 1);
                blue = startColor.blue_ + colorDiff.blue_ * pow((double)totalPixels / rangeTotal, 1);
                //green = 255 * (double)iterations / Mandelbrot::MAX_ITERATIONS;
                //green = green * green * green;
            }
            bitmap_.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::writeBitmap(std::string name)
{
    bitmap_.write(name);
}

void FractalCreator::addCenterShift(const Zoom &zoom)
{
    zoomlist_.updateDataCenter(zoom);
}

int FractalCreator::getRange(int iterations) const
{
    int range = 0;

    for (auto i = 1; i < ranges_.size(); i++)
    {
        range = i;
        if (ranges_[i] > iterations)
            break;
    }

    range--;
    assert(range > -1);
    assert(range < ranges_.size());
    return range;
}

FractalCreator::~FractalCreator()
{}
