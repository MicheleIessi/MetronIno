#pragma once

class MetronomeState;
#include "states/metronomeState.hh"
#include "tempo.hh"

class Metronome
{
public:
    MetronomeState* getCurrentState();
    Tempo* getCurrentTempo();

    void setState(MetronomeState* newState);

    void performAction();

    Metronome();
    ~Metronome();

private:
    bool initialised = false;
    MetronomeState* currentState;
    Tempo* currentTempo;
};