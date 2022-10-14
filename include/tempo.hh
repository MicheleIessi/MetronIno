#pragma once

#define DEFAULT_BPM             60
#define MIN_BPM                 15
#define MAX_BPM                 300

#define MAX_TIME_DIVISION       16
#define DEFAULT_TIME_SIGNATURE  FOUR_FOURTHS
#define BPM_TO_FREQ(x)          (60.0 / x) * 15625

typedef enum
{
    NO_BEAT,
    LOW_BEAT,
    MED_BEAT,
    HI_BEAT,
    MAX_BEAT_TYPES = HI_BEAT
} eBeatType;

typedef enum 
{
    FIRST_TIME_SIG,
    TWO_FOURTHS  = FIRST_TIME_SIG,
    THREE_FOURTHS,
    FOUR_FOURTHS,
    FIVE_FOURTHS,
    SIX_EIGHTS,
    SEVEN_EIGHTS,
    EIGHT_EIGHTS,
    NINE_EIGHTS,
    TWELVE_EIGHTS,
    LAST_TIME_SIG = TWELVE_EIGHTS,
    TIME_SIG_NUMBER
} eTimeSignature;

class Tempo
{
public:
    void setBPM(int newTempo);
    void setBPMFromArray(int* newTempo);
    void setBeat(int beat);
    void setTimeSignature(eTimeSignature newSignature);

    int getBPM();
    int getBeat();
    eTimeSignature getTimeSignature();

    void incrementBeat();

    Tempo();
    Tempo(int tempo, eTimeSignature sig);
    ~Tempo();

private:
    int bpm;
    int beat;
    eBeatType beatMatrix[TIME_SIG_NUMBER][MAX_TIME_DIVISION];
    eTimeSignature sig;
};