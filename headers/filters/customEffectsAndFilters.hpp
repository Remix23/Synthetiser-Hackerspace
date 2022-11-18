#pragma once
#include <baseEffect.hpp>

// test

// add here all additional filters in separate classess
// each of them has to override methods: calcParams and process

class Delay : public BaseEffect
{
private:
    float a, b, c;

public:
    Delay(float a, float b, float c, bool active);
    Delay(float a, float b, float c, bool active, bool debug);

    void calcParams(float td);
    float process(float sample);
};