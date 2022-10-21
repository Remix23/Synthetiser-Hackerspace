#pragma once

#include <waves.hpp>
#include <notes.hpp>
#include <config.hpp>
#include <mixer.hpp>

class Engine
{
public: 

    Channel channels [MAXTRACKS];

    Mixer mixer;
};