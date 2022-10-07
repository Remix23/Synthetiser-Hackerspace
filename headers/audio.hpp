#pragma once

#include <vector>

class AudioIOIf
{
public:
    AudioIOIf(){};
    ~AudioIOIf(){};

    virtual std::vector<double> *read(int sampleCount) = 0;
    virtual void write(std::vector<double> *buffer) = 0;
};