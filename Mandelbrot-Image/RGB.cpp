#include "RGB.h"



RGB::RGB(double r, double g, double b) : red_(r), green_(g), blue_(b)
{}

RGB operator-(const RGB &first, const RGB &second)
{
    return RGB(first.red_-second.red_, first.green_ - second.green_, first.blue_ - second.blue_);
}
