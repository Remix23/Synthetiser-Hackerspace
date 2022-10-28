#include <adsr.hpp>

ADSR::ADSR ()
{
};

void ADSR::computeForChannel (ADSRParams *params)
{
    switch (params->state)
    {
    case (1):
        params->state += params->attackRate;
        if (params->envelope >= 1) params->state = 2;
        break;

    case (2):
        params->envelope -= params->decayRate;
        if (params->envelope <= params->sustainLevel) params->state = 3;
        break;

    case (4):
        params->envelope -= params->realeaseRate;
        if (params->envelope <= 0) { params->state = 0; params->envelope = 0; }
        break;
}
};