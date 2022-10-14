#pragma once

#include "metronome.hh"
#include "states/metronomeState.hh"
#include "tempo.hh"

typedef enum
{
    FIRST_DIGIT,
    DIGIT_1 = FIRST_DIGIT,
    DIGIT_2,
    DIGIT_3,
    LAST_DIGIT = DIGIT_3,
    NUMBER_OF_DIGITS
} eDigit;

class ConfigTempoState : public MetronomeState
{
public:
    void enter(Metronome* m);
    void act(Metronome* m);
    void exit(Metronome* m);

    void resetTempo(Tempo* tempo);

    MetronomeState* nextState();

    static ConfigTempoState* getInstance()
    {
        static ConfigTempoState instance;
        return &instance;
    }

private:
    eDigit currentDigit;
    int    digits[NUMBER_OF_DIGITS];
};