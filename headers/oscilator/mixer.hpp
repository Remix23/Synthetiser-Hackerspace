#pragma once

#include <config.hpp>
#include <notes.hpp>

class Mixer
{
private:
    int sampleCount = MAXTRACKS;
    float sampleMix;

    float mix (Channel* tracks);

    float getMix();
};