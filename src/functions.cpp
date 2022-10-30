#include <functions.hpp>

double Interpolator::linearInterpolation (double x, double x1, double y1, double x2, double y2)
{
    return y1 + (y1 - y2) / (x1 - x2) * (x - x1);
}

double Interpolator::cubicSplineInterpolation()
{
    return 0.0;
}