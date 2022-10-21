#pragma once

#include <string>

enum Notes
{
    C,
    Cis,
    D,
    Dis,
    E,
    F,
    Fis,
    G,
    Gis,
    A,
    Ais,
    H
};

class NotesCalculator
{
public:

    NotesCalculator (int numOfSemitonsofBase, double baseFreq);
    ~NotesCalculator ();

    double GetFreqOfNote (int n); // n - the numbers of semitones from the base note

    int GetNumersOfSemitonesForNote ();

    std::string GetNoteNameFromSemitones (int numOfSemitonesFromStart); // the starting note is C0 
    int GetSemitonesFromNoteName (std::string noteName);

private:
    double baseFreq; // in Hz
    int semitonesFromStart;

    std::string baseNoteName; 
};
