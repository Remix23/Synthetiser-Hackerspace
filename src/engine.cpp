#include <engine.hpp>
#include <adsr.hpp>
#include <channel.hpp>

Engine::Engine() 
{

};

bool Engine::setTrack (Channel *channel, int n)
{
    if (n < 0 || n >= MAXTRACKS) return false;

    channels[n] = channel;

    return true;
};

void Engine::activateTrack (int n )
{
    channels[n]->activate();
};

void Engine::deativateTrack (int n)
{
    channels[n]->deactivate();
};

void Engine::calcStates()
{
    for (auto ch : channels)
    {
        adsr.computeForChannel(ch->getASDRps());
    }
};

double Engine::process()
{
    double sample = 0;
    for (auto ch : channels)
    {
    }
    return sample;
};