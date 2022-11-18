#include <channel.hpp>
#include <notes.hpp>
#include <waveTableOscilator.hpp>
#include <config.hpp>

Channel::Channel (bool debug)
{
    active = false;
    isKeyPressed = false;

    adsrps.attackRate = 0;
    adsrps.decayRate = 0;
    adsrps.sustainLevel = 0;
    adsrps.envelope = 0;
    adsrps.state = 0;
    adsrps.realeaseRate = 0;

    oscps.freq = 0;
    oscps.phase = 0;
    oscps.step = 0;
    oscps.waveName = Sin;

    this->debug = debug;
}

Channel::Channel(){}

void Channel::activate ()
{
    active = true;
}

void Channel::deactivate()
{
    active = false;
}

bool Channel::isActive ()
{
    return active;
}

void Channel::keyPressed ()
{
    isKeyPressed = true;
    adsrps.state = 1;
    adsrps.envelope = 0;
}

void Channel::keyReleased ()
{
    adsrps.state = 4;
    isKeyPressed = false;
}

bool Channel::getKeyState()
{
    return isKeyPressed;
}

void Channel::setFreq (float freq)
{
    oscps.freq = freq;
    oscps.step = WAVETABLELENGHT * freq / SAMPLERATE;
    oscps.phase = 0;
}

float Channel::getFreq()
{
    return oscps.freq;
}

void Channel::changeWave(WaveName new_name)
{
    oscps.waveName = new_name;
    oscps.phase = 0;
}

OscilatorParams* Channel::getOscParams ()
{
    return &oscps;
}

ADSRParams* Channel::getASDRps()
{
    return &adsrps;
};

