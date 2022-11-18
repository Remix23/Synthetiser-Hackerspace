#pragma once

struct ADSRParams
{
    char state = 0;

    float attackRate;
    float decayRate;
    float realeaseRate;
    float sustainLevel;

    float envelope = 0;
};

class ADSR
{

public:
    ADSR();

    void computeForChannel(ADSRParams &params);
};