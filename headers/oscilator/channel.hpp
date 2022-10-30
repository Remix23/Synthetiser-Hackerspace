#pragma once
#include <string>

#include <waves.hpp>
#include <notes.hpp>
#include <adsr.hpp>
#include <waveTableOscilator.hpp>

class Channel 
{
private:

    std::string noteName;
    int semitonesFromB; 

    bool active;

    int key; 
    bool isKeyPressed;

    WaveName wavenName;

    ADSRParams adsrps;

    OscilatorParams oscps;

public: 

    Channel ();

    void activate ();
    void deactivate ();

    bool isActive ();

    void keyPressed ();
    void keyReleased ();

    bool getKeyState ();

    void setFreq (double freq);
    double getFreq ();

    ADSRParams* getASDRps ();

    OscilatorParams* getOscParams ();

};