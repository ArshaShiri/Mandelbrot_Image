#include <iostream>
#include "Mandelbrot.h"



using namespace std;

Mandelbrot::Mandelbrot()
{}

//int Mandelbrot::getIterationsComplex(double x, double y)
//{
//    complex<double> z = 0;
//    complex<double> c(x,y);
//    int iterations = 0;
//    while (iterations < MAX_ITERATIONS)
//    {
//        z = z * z + c;
//        if (abs(z) > 2)
//            break;
//        iterations++;
//    }
//    return iterations;
//}

int Mandelbrot::getNumberOfIterations(double x, double y)
{
    std::pair<double, double> z(0.0, 0.0);
    std::pair<double, double> c(0.0, 0.0);
    c.first = x;
    c.second = y;

    int iterations = 0;
    while (iterations < MAX_ITERATIONS)
    {
        auto zxMid = (z.first * z.first) - (z.second * z.second) + x;
        auto zyMid = (2 * z.first * z.second) + y;
        z.first = zxMid;
        z.second = zyMid;
        if (sqrt((z.first * z.first) + (z.second * z.second)) > 2)
            break;
        iterations++;
    }
    return iterations;
}


Mandelbrot::~Mandelbrot()
{}
