#include <math.h>

class Interpolator 
{
public: 
    static double linearInterpolation (double x, double x1, double y1, double x2, double y2);

    static double cubicSplineInterpolation ();
};