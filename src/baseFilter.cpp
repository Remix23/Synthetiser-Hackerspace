#include <baseFilter.hpp>

void BaseFilter::activate ()
{
    active = true;
}

void BaseFilter::deactivate ()
{
    active = false;
}

bool BaseFilter::isActive()
{
    return active;
}