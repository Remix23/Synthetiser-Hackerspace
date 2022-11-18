#include <functions.hpp>

float Interpolator::linearInterpolation(float x, float x1, float y1, float x2, float y2)
{
    return y1 + (y1 - y2) / (x1 - x2) * (x - x1);
}

float Interpolator::cubicSplineInterpolation()
{
    return 0.0;
}