#include <engine.hpp>
#include <adsr.hpp>
#include <channel.hpp>
#include <config.hpp>
#include <iostream>
#include <vector>
#include <baseEffect.hpp>
#include <customEffectsAndFilters.hpp>

Engine::Engine(bool debug) 
{

    this->debug = debug;

    ADSR adsr = ADSR();

    WaveTableOscilator osc = WaveTableOscilator();

    for (int i = 0; i < MAXTRACKS; i++)
    {
        channels[i] = Channel(debug);
        if (debug) std::cout << "created " << i << "th channel" << std::endl;
    }

    effects = std::vector<BaseEffect>();
    filters = std::vector<BaseEffect>();

    filters.push_back(Delay(1.0, 2.0, 3.0, true, debug));

    // adding filters and effects

};

Engine::Engine (){}

Engine::~Engine ()
{
    if (debug) std::cout << "engine removal" << std::endl;
}

bool Engine::_isValidN (int n)
{
    return 0 <= n < MAXTRACKS;
}

bool Engine::setTrack (int n, double freq)
{
    if (!_isValidN(n)) return false;

    channels[n].setFreq(freq);

    return true;
};

bool Engine::activateTrack (int n)
{
    if (!_isValidN(n)) return false;

    channels[n].activate();
    return true;
};

bool Engine::deativateTrack (int n)
{
    if (!_isValidN(n)) return false;

    channels[n].activate();
    return true;
};

bool Engine::changeWave (int n, WaveName new_name)
{
    if (!_isValidN(n)) return false;

    channels[n].changeWave(new_name);
    return true;
}

void Engine::calcStates()
{
    for (auto &ch : channels)
    {
        adsr.computeForChannel(*ch.getASDRps());
    }
    for (auto &f : filters)
    {
        f.calcParams(1 / SAMPLERATE);
    }
    for (auto &e : effects)
    {
        e.calcParams(1 / SAMPLERATE);
    }
};

double Engine::process()
{
    double sample = 0;
    for (auto &ch : channels)
    {
        if (!ch.isActive()) continue;

        double s = osc.getSample(*ch.getOscParams());
        s *= ch.getASDRps()->envelope;
        sample += s;
    }
    sample /= MAXTRACKS;
    for (auto &e : effects)
    {
        if (e.isActive()) e.process(sample);
    }
    for (auto &f : filters)
    {
        if (f.isActive()) sample = f.process(sample);
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