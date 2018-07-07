#pragma once

#include <utility>
#include <vector>

#include "Zoom.h"

class ZoomList
{
private:
    double xCenter_{0};
    double yCenter_{0};
    double scale_{1.0};
    int width_{0};
    int height_{0};
    std::vector<Zoom> zooms;
public:
    ZoomList() = default;
    ZoomList(int width, int height);
    void add(const Zoom &zoom);
    std::pair<double, double> doZoom(int x, int y);
};