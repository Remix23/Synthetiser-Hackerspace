#pragma once

#include <adsr.hpp>
#include <channel.hpp>
#include <config.hpp>
#include <baseFilter.hpp>

class Engine
{
private: 

    Channel* channels [MAXTRACKS];

    ADSR adsr;

    BaseFilter filters[];

public:

    Engine ();

    double process ();

    bool setTrack (Channel *channel, int n);

    void activateTrack (int n);

    void deativateTrack (int n);

    void calcStates ();

};