#pragma once

#include "metronome.hh"
#include "states/metronomeState.hh"
#include "tempo.hh"

class ConfigTimeSigState : public MetronomeState
{
public:
    void enter(Metronome* m);
    void act(Metronome* m);
    void exit(Metronome* m);

    MetronomeState* nextState();

    static ConfigTimeSigState* getInstance()
    {
        static ConfigTimeSigState instance;
        return &instance;
    }

private:
    eTimeSignature currentSig;
};