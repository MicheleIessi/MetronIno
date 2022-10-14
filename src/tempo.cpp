#include "tempo.hh"
#include "utils.hh"

static int defaultBeatMatrix[TIME_SIG_NUMBER][MAX_TIME_DIVISION] =
{
    /**     1         2         3         4         5         6         7         8         9        10        11        12        13        14        15        16 */
    { HI_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT,  NO_BEAT,  NO_BEAT,  NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },        // 3/4
    { HI_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT,  NO_BEAT,  NO_BEAT,  NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },        // 3/4
    { HI_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT,  NO_BEAT,  NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },        // 4/4
    { HI_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT,  NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },        // 5/4
    { HI_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },        // 6/8
    { HI_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },       // 7/8
    { HI_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },      // 8/8
    { HI_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT },     // 9/8
    { HI_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, MED_BEAT, LOW_BEAT, LOW_BEAT, LOW_BEAT, NO_BEAT, NO_BEAT, NO_BEAT, NO_BEAT }   // 12/8
};

static int maxBeats[TIME_SIG_NUMBER] = 
{
    2, 3, 4, 5, 6, 7, 8, 9, 12 
};

Tempo::Tempo()
{
    setBPM(DEFAULT_BPM);
    this->sig = DEFAULT_TIME_SIGNATURE;

    memcpy(beatMatrix, defaultBeatMatrix, sizeof(defaultBeatMatrix));
};

Tempo::Tempo(int bpm, eTimeSignature sig)
{
    setBPM(bpm);
    this->sig = sig;
    this->beat = 0;
}

int Tempo::getBPM()
{
    return this->bpm;
}

int Tempo::getBeat()
{
    int currBeat = beat % maxBeats[sig];
    return defaultBeatMatrix[sig][currBeat];
}

void Tempo::setBPM(int bpm)
{
    if (bpm > MAX_BPM) bpm = MAX_BPM;
    if (bpm < MIN_BPM) bpm = MIN_BPM;
    this->bpm = bpm;
    DEBUG_PRINT("New tempo: "); DEBUG_PRINTLN(this->bpm);
}

void Tempo::setBPMFromArray(int* bpm)
{
    int newBPM = (bpm[0] * 100) + (bpm[1] * 10) + bpm[2];
    setBPM(newBPM);
}

void Tempo::setTimeSignature(eTimeSignature sig)
{
    this->sig = sig;
}

void Tempo::setBeat(int beat)
{
    this->beat = beat;
}

void Tempo::incrementBeat()
{
    this->beat += 1;
}
