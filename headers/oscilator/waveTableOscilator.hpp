#pragma once

#include <waves.hpp>

struct OscilatorParams
{
    float phase;
    float step;

    float freq;

    WaveName waveName;
};

class WaveTableOscilator
{

public:
    float getSample(OscilatorParams &params);
};