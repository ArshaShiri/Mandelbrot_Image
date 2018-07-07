#include <complex>
#include "Mandelbrot.h"



using namespace std;

Mandelbrot::Mandelbrot()
{}

int Mandelbrot::getIterationsComplex(double x, double y)
{
    complex<double> z = 0;
    complex<double> c(x,y);
    int iterations = 0;
    while (iterations < MAX_ITERATIONS)
    {
        z = z * z + c;
        if (abs(z) > 2)
            break;
        iterations++;
    }
    return iterations;
}

int Mandelbrot::getIterations(double x, double y)
{
    auto zx = 0.0;
    auto zy = 0.0;
    auto cx = x;
    auto cy = y;

    int iterations = 0;
    while (iterations < 1000)
    {
        auto zxMid = (zx * zx) - (zy * zy) + x;
        auto zyMid = (2 * zx * zy) + y;
        zx = zxMid;
        zy = zyMid;
        if (sqrt((zx * zx) + (zy * zy)) > 2)
            break;
        iterations++;
    }
    return iterations;
}


Mandelbrot::~Mandelbrot()
{}
