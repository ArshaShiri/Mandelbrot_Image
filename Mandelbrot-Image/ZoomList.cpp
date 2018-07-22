#include <iostream>
#include "ZoomList.h"


ZoomList::ZoomList(int width, int height) : width_(width), height_(height){}

void ZoomList::updateDataCenter(const Zoom &zoom) 
{
    zooms.push_back(zoom);

    xCenter_ += (zoom.x - width_ / 2) * scale_;
    yCenter_ += (zoom.y - height_ / 2) * scale_;
    if (zoom.scale != 0) scale_ /= zoom.scale;
    else std::cout << "Divided by zero" << std::endl;
}                                                                               

std::pair<double, double> ZoomList::getCoordinates(int x, int y)
{
    double xFractal = (x - width_ / 2) * scale_ +xCenter_;
    double yFractal = (y - height_ / 2) * scale_ +yCenter_;

    return std::pair<double, double> (xFractal, yFractal);
}