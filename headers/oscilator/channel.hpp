#pragma once
#include <string>

#include <waves.hpp>
#include <notes.hpp>
#include <adsr.hpp>

class Channel 
{
private:

    std::string noteName;
    float freq;
    int semitonesFromB; 

    bool active = false;

    WaveNames wavenName;

    ADSRParams adsrps;

public: 

    Channel ();

    ~Channel();

    void activate ();
    void deactivate ();

    ADSRParams* getASDRps ();

};