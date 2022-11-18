#include <baseEffect.hpp>
#include <customEffectsAndFilters.hpp>

Delay::Delay(float a, float b, float c, bool active) : BaseEffect(active)
{
    this->a = a;
    this->b = b;
    this->c = c;
}
Delay::Delay(float a, float b, float c, bool active, bool debug) : BaseEffect(active, debug)
{
    this->a = a;
    this->b = b;
    this->c = c;
}

void Delay::calcParams(float td)
{
    a = 2 * b;
    b = c * c;
    c++;
}

float Delay::process(float sample)
{
    return sample / a * b / c;
}