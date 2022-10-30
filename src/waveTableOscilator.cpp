#include <waveTableOscilator.hpp>
#include <functions.hpp>
#include <waves.hpp>
#include <math.h>
#include <config.hpp>

double WaveTableOscilator::getSample (OscilatorParams &params)
{
    params.phase += params.step;

    double* table = waveTables[params.waveName];

    if (params.phase >= WAVETABLELENGHT) params.phase -= WAVETABLELENGHT;

    // double x1 = table[(int *) params.phase];

    // return Interpolator::linearInterpolation();
    return 1;
};



