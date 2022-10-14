#pragma once

#include "metronome.hh"
#include "tempo.hh"

#include <Arduino.h>

#define DEFAULT_H_FREQ          3000
#define DEFAULT_M_FREQ          1500
#define DEFAULT_L_FREQ          1000

#define DEFAULT_TONE_DURATION   10

class ToneHandler
{
public:

    void generateTone();
    void setMetronome(Metronome* m);
    void testTones();

    static ToneHandler* getInstance()
    {
        static ToneHandler instance;
        return &instance;
    }

private:
    Metronome* m;
    ToneHandler();
    int beatFreqs[MAX_BEAT_TYPES];
};