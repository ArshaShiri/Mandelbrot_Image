#include "FractalCreator.h"
#include <iostream>
#include <assert.h>

FractalCreator::FractalCreator(int width, int height) :
    total_(0),
    width_(width),
    height_(height),
    histogram_(new int[Mandelbrot::MAX_ITERATIONS]()),
    fractal_(new int[width_ * height_]()),
    bitmap_(width, height),
    zoomlist_(width, height)
{
    zoomlist_.add(Zoom(width / 2, height / 2, 4.0 / width));
}


void FractalCreator::run(std::string name)
{
    calculateIterations();
    calculateTotalIterations();
    calculateRangeTotals();
    drawFractal();
    writeBitmap("test.bmp");
}


void FractalCreator::calculateIterations()
{
    for (double y = 0; y < height_; y++)
    {
        for (double x = 0; x < width_; x++)
        {
            std::pair<double, double> coords = zoomlist_.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first, coords.second);
            fractal_[y * width_ + x] = iterations;
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                histogram_[iterations]++;
            }
        }
    }
}

void FractalCreator::calculateTotalIterations()
{
    for (auto i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        total_ += histogram_[i];
    }
}


void FractalCreator::drawFractal()
{
    RGB startColor(0, 0, 0);
    RGB endtColor(0, 0, 255);
    RGB colorDiff = endtColor - startColor;
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
                double hue = 0.0;
                for (auto i = rangeStart; i <= iterations; i++)
                {
                    totalPixels += histogram_[i];
                }
                red = startColor.red_ + colorDiff.red_ * (double)totalPixels / rangeTotal;
                green = startColor.green_ + colorDiff.green_ * (double)totalPixels / rangeTotal;
                blue = startColor.blue_ + colorDiff.blue_ * (double)totalPixels / rangeTotal;
            }
            bitmap_.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::addZoom(const Zoom &zoom)
{
    zoomlist_.add(zoom);
}

void FractalCreator::writeBitmap(std::string name)
{
    bitmap_.write(name);
}

void FractalCreator::addRange(double rangeEndIteration, const RGB &rgb)
{
    ranges_.push_back(rangeEndIteration * Mandelbrot::MAX_ITERATIONS);
    colors_.push_back(rgb);

    if (gotFirstRange)
    {
        rangesTotal_.push_back(0);
    }
    gotFirstRange = true;


}

void FractalCreator::calculateRangeTotals()
{
    int rangeIndex = 0;
    for (auto i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        int pixels = histogram_[i];
        if (i >= ranges_[rangeIndex + 1])
            rangeIndex++;
        rangesTotal_[rangeIndex] += pixels;
    }
    for (int value : rangesTotal_)
    {
        std::cout << value << std::endl;
    }
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
