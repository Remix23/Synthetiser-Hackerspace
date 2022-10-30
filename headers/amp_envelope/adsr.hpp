#pragma once

struct ADSRParams 
{
    char state = 0;
    
    double attackRate;
    double decayRate;
    double realeaseRate;
    double sustainLevel;

    double envelope = 0;
};

class ADSR 
{

public:

    ADSR ();

    void computeForChannel (ADSRParams &params);
};