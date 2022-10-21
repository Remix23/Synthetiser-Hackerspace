#include <notes.hpp>
#include <math.h>
#include <string>

NotesCalculator::NotesCalculator (int numOfSemitonsofBase, double baseFreq) {
    this->semitonesFromStart = numOfSemitonsofBase;
    this->baseFreq = baseFreq;
    
}

double NotesCalculator::GetFreqOfNote (int n) 
{
    return this->baseFreq * std::pow(1.05946309, n);
}

int NotesCalculator::GetSemitonesFromNoteName (std::string noteName)
{

}