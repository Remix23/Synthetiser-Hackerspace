#pragma once
#include <baseEffect.hpp>

// test

// add here all additional filters in separate classess
// each of them has to override methods: calcParams and process

class Delay : public BaseEffect
{
private:

double a, b, c;

public:

    Delay(double a, double b, double c, bool active);
    Delay (double a, double b, double c, bool active, bool debug);

    void calcParams (double td);
    double process (double sample);
};