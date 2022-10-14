#pragma once

#include "states/metronomeState.hh"

class IdleState : public MetronomeState
{
public:    
    void enter(Metronome* m);
    void act(Metronome* m);
    void exit(Metronome* m);
    
    MetronomeState* nextState();

    static IdleState* getInstance()
    {
        static IdleState instance;
        return &instance;
    }
};