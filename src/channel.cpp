#include <channel.hpp>
#include <notes.hpp>

ADSRParams* Channel::getASDRps()
{
    return &adsrps;
};

void Channel::activate ()
{
    active = true;
}

void Channel::deactivate()
{
    active = false;
}