#include <baseEffect.hpp>

BaseEffect::BaseEffect()
{
    active = false;
    debug = false;
}

BaseEffect::BaseEffect(bool active)
{
    this->active = active;
    this->debug = false;
}

BaseEffect::BaseEffect(bool active, bool debug)
{
    this->active = active;
    this->debug = debug;
}

BaseEffect::~BaseEffect() {}

void BaseEffect::activate()
{
    active = true;
}

void BaseEffect::deactivate()
{
    active = false;
}

bool BaseEffect::isActive()
{
    return active;
}

void BaseEffect::calcParams(float td) {}
float BaseEffect::process(float sample) { return sample; }