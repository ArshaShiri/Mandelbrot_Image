#pragma once

struct RGB
{
    double red_;
    double green_;
    double blue_;
    RGB(double r, double g, double b);
};

RGB operator-(const RGB &first, const RGB &second);

