#include <mixer.hpp>
#include <notes.hpp>

Mixer::mix (Channel* tracks)
{
    for (int i = 0; i < sampleCount; i++)
    {
        sampleMix += tracks[i].sample;
    }
    sampleMix /= sampleCount;
    return sampleMix;
}

Mixer::getMix()
{
    return sampleMix;
}