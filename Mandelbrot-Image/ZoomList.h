#pragma once

#include <utility>
#include <vector>

#include "Zoom.h"

class ZoomList
{
private:
    double xCenter_{0};
    double yCenter_{0};
    double xCenterMapped_{0};
    double yCenterMapped_{0};
    double scale_{1.0};


    int width_{0};
    int height_{0};
    std::vector<Zoom> zooms;
public:
    ZoomList() = default;
    ZoomList(int width, int height);

    // Adding zoom, the Zoom class takes pixels
    void updateDataCenter(const Zoom &zoom);
    std::pair<double, double> getCoordinates(int x, int y);
};