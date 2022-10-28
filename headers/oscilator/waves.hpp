#pragma once
#include <config.hpp>

enum WaveNames 
{
    Sin, 
    Cos, 
    Saw, 
    Square
};

float sinTable [WAVATABLELENGHT] = {
1.0f
};

float cosTable [WAVATABLELENGHT];

float sawTable [WAVATABLELENGHT] = {
1.0f
};

float squareTable [WAVATABLELENGHT] = {
1.0f
};

float* waveTables [4] = {
    sinTable,
    cosTable, 
    sawTable, 
    squareTable,
};