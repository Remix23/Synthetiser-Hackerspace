#pragma once

#include <adsr.hpp>
#include <channel.hpp>
#include <config.hpp>
#include <baseEffect.hpp>
#include <waveTableOscilator.hpp>
#include <vector>

class Engine
{
private:
    bool debug = true;

    Channel channels[MAXTRACKS];

    ADSR adsr;

    WaveTableOscilator osc;

    std::vector<BaseEffect> effects;
    std::vector<BaseEffect> filters;

    bool _isValidN(int n);

public:
    Engine();
    Engine(bool debug);

    ~Engine();

    void printChannels();

    // track management

    bool setTrack(int n, float freq);

    bool activateTrack(int n);

    bool deativateTrack(int n);

    bool changeWave(int n, WaveName new_name);

    // sound proccesing

    void calcStates();

    float process();

    void keyPressed(int key);

    // filters and effects menagemennt

    void activateFilter();
    void deativateFilter();

    void activateEffect();
    void deactivateEffect();
};