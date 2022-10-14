#pragma once

// Metronome forward declaration to fix circular dependency
class Metronome;
#include "metronome.hh"

class MetronomeState
{
    
public:
    virtual void enter(Metronome* m) = 0;
    virtual void act(Metronome* m) = 0;
    virtual void exit(Metronome* m) = 0;

    virtual MetronomeState* nextState() = 0;
};