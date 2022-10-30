#pragma once

#include <math.h>
#include <waves.hpp>

struct OscilatorParams 
{
    double phase;
    double step;

    double freq;

    WaveName waveName;
};

class WaveTableOscilator
{

public:
    
    double getSample (OscilatorParams &params);
    
};