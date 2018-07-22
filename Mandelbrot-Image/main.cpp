#include <iostream>
#include <memory>
#include <math.h>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "FractalCreator.h"
#include "RGB.h"


using namespace std;

int main()
{
    FractalCreator fractalCreator(800, 600, 200.0);
    fractalCreator.addRange(0, RGB(0, 0, 0));
    fractalCreator.addRange(0.1, RGB(255, 0, 0));
    fractalCreator.addRange(0.2, RGB(255, 255, 0));
    fractalCreator.addRange(0.3, RGB(255, 255, 255));
    fractalCreator.addRange(0.5, RGB(0, 255, 0));
    fractalCreator.addRange(1.0, RGB(255, 255, 255));
    fractalCreator.addCenterShift(Zoom(295, 398, 10));
    fractalCreator.addCenterShift(Zoom(295, 296, 10));

    fractalCreator.run("FinalTest.bmp");
    cout << "Finished" << endl;
    return 0;
}