#include <engine.hpp>
#include <adsr.hpp>
#include <channel.hpp>
#include <config.hpp>
#include <iostream>
#include <vector>

Engine::Engine() 
{

    ADSR adsr = ADSR();

    WaveTableOscilator osc = WaveTableOscilator();

    for (int i = 0; i < MAXTRACKS; i++)
    {
        channels[i] = Channel();
        std::cout << "created " << i << "th channel" << std::endl;
    }

    filters = std::vector<BaseFilter>();

};

Engine::~Engine ()
{
    std::cout << "engine removal" << std::endl;
}

bool Engine::setTrack (double freq, int n)
{
    if (n < 0 || n >= MAXTRACKS) return false;

    channels[n].setFreq(freq);

    return true;
};

void Engine::activateTrack (int n)
{
    channels[n].activate();
};

void Engine::deativateTrack (int n)
{
    channels[n].activate();
};

void Engine::calcStates()
{
    for (auto &ch : channels)
    {
        adsr.computeForChannel(ch.getASDRps());
    }
};

double Engine::process()
{
    double sample = 0;
    for (auto &ch : channels)
    {
        osc.getSample(*ch.getOscParams());
    }
    return sample;
};

void Engine::printChannels()
{
    std::cout << "Printting Channels..." << std::endl;
    for (int i = 0; i < MAXTRACKS; i++)
    {
        std::cout << "Channel: " << i << " | freq: " << channels[i].getFreq() << " | is active: " << channels[i].isActive() << std::endl;
    }
}