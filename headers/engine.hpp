#pragma once

#include <adsr.hpp>
#include <channel.hpp>
#include <config.hpp>
#include <baseFilter.hpp>
#include <waveTableOscilator.hpp>
#include <vector>

class Engine
{
public: 

    Channel channels [MAXTRACKS];

    ADSR adsr;

    WaveTableOscilator osc;

    std::vector <BaseFilter> filters;

public:

    Engine ();

    ~Engine ();

    void printChannels ();

    // track management

    bool setTrack (double freq, int n);

    void activateTrack (int n);

    void deativateTrack (int n);

    // sound proccesing

    void calcStates ();

    double process ();

    void keyPressed (int key);

    // filters

};