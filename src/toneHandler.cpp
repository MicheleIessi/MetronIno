#include "toneHandler.hh"
#include "utils.hh"
#include "pins.hh"

ToneHandler::ToneHandler()
{
    beatFreqs[NO_BEAT] = 0;
    beatFreqs[LOW_BEAT] = DEFAULT_L_FREQ;
    beatFreqs[MED_BEAT] = DEFAULT_M_FREQ;
    beatFreqs[HI_BEAT]  = DEFAULT_H_FREQ;
}

void ToneHandler::setMetronome(Metronome* m)
{
    this->m = m;
}

void ToneHandler::generateTone()
{
    Tempo* t = m->getCurrentTempo();
    int currentBeat = t->getBeat();
    //DEBUG_PRINT("Generate tone: "); DEBUG_PRINTLN(beatFreqs[currentBeat]);
    tone(SOUND_PIN, beatFreqs[currentBeat], DEFAULT_TONE_DURATION);
}

void ToneHandler::testTones()
{
    int w = 50;

    tone(SOUND_PIN, DEFAULT_L_FREQ, w); delay(w);
    tone(SOUND_PIN, DEFAULT_M_FREQ, w); delay(w);
    tone(SOUND_PIN, DEFAULT_H_FREQ, w); delay(w);
}