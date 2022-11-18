#pragma once
#include <string>

#include <waves.hpp>
#include <notes.hpp>
#include <adsr.hpp>
#include <waveTableOscilator.hpp>

class Channel
{
private:
    bool debug = false;

    std::string noteName;
    int semitonesFromB;

    bool active;

    int key;
    bool isKeyPressed;

    ADSRParams adsrps;

    OscilatorParams oscps;

public:
    Channel();
    Channel(bool debug);

    void activate();
    void deactivate();

    bool isActive();

    void keyPressed();
    void keyReleased();

    bool getKeyState();

    void setFreq(float freq);
    float getFreq();

    void changeWave(WaveName new_name);

    ADSRParams *getASDRps();

    OscilatorParams *getOscParams();
};