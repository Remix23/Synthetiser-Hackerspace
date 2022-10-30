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

    double y1 = table[(int)params.phase];
    double y2= table[(int)params.phase + 1];

    return Interpolator::linearInterpolation(params.phase, std::floor(params.phase), y1, std::ceil(params.phase), y2);
};
