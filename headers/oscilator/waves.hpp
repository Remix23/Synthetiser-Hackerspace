#pragma once

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

float cosTable [WAVATABLELENGHT] = {
1.0f
};

float sawTable [WAVATABLELENGHT] = {
1.0f
};

float squareTable [WAVATABLELENGHT] = {
1.0f
};

float waveTables [][WAVATABLELENGHT] = {
    sinTable,
    cosTable, 
    sawTable, 
    squareTable
};