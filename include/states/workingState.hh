#pragma once

#include "states/metronomeState.hh"

class WorkingState : public MetronomeState
{
public:    
    void enter(Metronome* m);
    void act(Metronome* m);
    void exit(Metronome* m);
    
    MetronomeState* nextState();

    static WorkingState* getInstance()
    {
        static WorkingState instance;
        return &instance;
    }

};