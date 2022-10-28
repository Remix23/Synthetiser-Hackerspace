#pragma once

enum WaveNames 
{
    Sin, 
    Cos, 
    Saw, 
    Square
};

const float sinTable [128] = {
1.0f
};

const float cosTable [128] = {
1.0f
};

const float sawTable [128] = {
1.0f
};

const float squareTable [128] = {
1.0f
};

const float waveTables [4][] = {
    sinTable,
    cosTable, 
    sawTable, 
    squareTable
};