#include <baseEffect.hpp>
#include <customEffectsAndFilters.hpp>

Delay::Delay (double a, double b, double c, bool active):BaseEffect(active)
{ 
    this->a = a;
    this->b = b;
    this->c = c;
}
Delay::Delay (double a, double b, double c, bool active, bool debug):BaseEffect(active, debug)
{ 
    this->a = a;
    this->b = b;
    this->c = c;
}

void Delay::calcParams(double td)
{
    a = 2 * b;
    b = c * c;
    c++;
}

double Delay::process(double sample)
{
    return sample / a * b / c;
}