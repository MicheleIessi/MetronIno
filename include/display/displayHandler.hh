#pragma once

#include "tempo.hh"

#define CHAR_0      0x5F
#define CHAR_1      0x44
#define CHAR_2      0x9D
#define CHAR_3      0xD5
#define CHAR_4      0xC6
#define CHAR_5      0xD3
#define CHAR_6      0xDB
#define CHAR_7      0x45
#define CHAR_8      0xDF
#define CHAR_9      0xD7
#define CHAR_A      0xCF
#define CHAR_B      0xDA
#define CHAR_C      0x1B
#define CHAR_D      0xDC
#define CHAR_E      0x9B
#define CHAR_F      0x8B
#define CHAR_NULL   0x00
#define CHAR_MINUS  0x80
#define CHAR_DP     0x20

#define NUMBER_OF_CHARS 16

#define DEFAULT_BRIGHTNESS  70
#define BLINKING_TIME       500 // ms

class DisplayHandler
{
    public:
        void initialise();
        void refresh();
        void setNumber(int number);
        void setTimeSignature(eTimeSignature sig);

        void toggleBlinking(int digit);
        void allOn();

        void displayInteger(int integer);
        void displayIntegerArray(int* intArray);
        void displayTimeSignature();
        void displayIdle();

        static DisplayHandler* getInstance()
        {
            static DisplayHandler instance;
            return &instance;
        };

    private:
        DisplayHandler();
        char charTable[NUMBER_OF_CHARS];
        int timeSigTable[TIME_SIG_NUMBER][4];
        bool charOn[NUMBER_OF_CHARS];
        int lastNumber;
        int signature;
        int brightness;
};