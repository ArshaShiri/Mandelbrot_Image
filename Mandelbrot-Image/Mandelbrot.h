#pragma once

class Mandelbrot
{
public:
    static const int MAX_ITERATIONS = 1000;
    Mandelbrot();
    ~Mandelbrot();

    // This method uses a complex library (This seems to be very slow)
    static int getIterationsComplex(double x, double y);

    // The algorithm of this method is written without using any library 
    static int getIterations(double x, double y);
};

