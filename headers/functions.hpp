#include <math.h>

class Interpolator
{
public:
    static float linearInterpolation(float x, float x1, float y1, float x2, float y2);

    static float cubicSplineInterpolation();
};