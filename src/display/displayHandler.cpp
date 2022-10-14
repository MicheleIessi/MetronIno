#include "display/displayHandler.hh"
#include "pins.hh"
#include "utils.hh"

#include <Arduino.h>

char controlDigits[] = { DIGIT_0_PIN, DIGIT_1_PIN, DIGIT_2_PIN, DIGIT_3_PIN };
byte dd[] = { 0, 0, 0, 0, 0 };

DisplayHandler::DisplayHandler()
{
    DEBUG_PRINTLN("Entering DisplayHandler Constructor");

    lastNumber = 0;
    brightness = DEFAULT_BRIGHTNESS;

    memset(charTable, 0, sizeof(charTable));
    memset(timeSigTable, 0, sizeof(timeSigTable));

    /** Initialise character table */
    charTable[0] = CHAR_0; charTable[1] = CHAR_1; charTable[2] = CHAR_2; charTable[3] = CHAR_3;
    charTable[4] = CHAR_4; charTable[5] = CHAR_5; charTable[6] = CHAR_6; charTable[7] = CHAR_7;
    charTable[8] = CHAR_8; charTable[9] = CHAR_9; charTable[10] = CHAR_A; charTable[11] = CHAR_B;
    charTable[12] = CHAR_C; charTable[13] = CHAR_D; charTable[14] = CHAR_E; charTable[15] = CHAR_F;

    /** Initialise time signature table */
    timeSigTable[TWO_FOURTHS][3] = CHAR_NULL;
    timeSigTable[TWO_FOURTHS][2] = CHAR_2;
    timeSigTable[TWO_FOURTHS][1] = CHAR_4;
    timeSigTable[TWO_FOURTHS][0] = CHAR_NULL;

    timeSigTable[THREE_FOURTHS][3] = CHAR_NULL;
    timeSigTable[THREE_FOURTHS][2] = CHAR_3;
    timeSigTable[THREE_FOURTHS][1] = CHAR_4;
    timeSigTable[THREE_FOURTHS][0] = CHAR_NULL;

    timeSigTable[FOUR_FOURTHS][3] = CHAR_NULL;
    timeSigTable[FOUR_FOURTHS][2] = CHAR_4;
    timeSigTable[FOUR_FOURTHS][1] = CHAR_4;
    timeSigTable[FOUR_FOURTHS][0] = CHAR_NULL;

    timeSigTable[FIVE_FOURTHS][3] = CHAR_NULL;
    timeSigTable[FIVE_FOURTHS][2] = CHAR_5;
    timeSigTable[FIVE_FOURTHS][1] = CHAR_4;
    timeSigTable[FIVE_FOURTHS][0] = CHAR_NULL;

    timeSigTable[SIX_EIGHTS][3] = CHAR_NULL;
    timeSigTable[SIX_EIGHTS][2] = CHAR_6;
    timeSigTable[SIX_EIGHTS][1] = CHAR_8;
    timeSigTable[SIX_EIGHTS][0] = CHAR_NULL;

    timeSigTable[SEVEN_EIGHTS][3] = CHAR_NULL;
    timeSigTable[SEVEN_EIGHTS][2] = CHAR_7;
    timeSigTable[SEVEN_EIGHTS][1] = CHAR_8;
    timeSigTable[SEVEN_EIGHTS][0] = CHAR_NULL;

    timeSigTable[EIGHT_EIGHTS][3] = CHAR_NULL;
    timeSigTable[EIGHT_EIGHTS][2] = CHAR_8;
    timeSigTable[EIGHT_EIGHTS][1] = CHAR_8;
    timeSigTable[EIGHT_EIGHTS][0] = CHAR_NULL;

    timeSigTable[NINE_EIGHTS][3] = CHAR_NULL;
    timeSigTable[NINE_EIGHTS][2] = CHAR_9;
    timeSigTable[NINE_EIGHTS][1] = CHAR_8;
    timeSigTable[NINE_EIGHTS][0] = CHAR_NULL;

    timeSigTable[TWELVE_EIGHTS][3] = CHAR_1;
    timeSigTable[TWELVE_EIGHTS][2] = CHAR_2;
    timeSigTable[TWELVE_EIGHTS][1] = CHAR_8;
    timeSigTable[TWELVE_EIGHTS][0] = CHAR_NULL;

    /** Adding decimal points to second digits */
    for (int sig = FIRST_TIME_SIG; sig <= LAST_TIME_SIG; sig++)
    {
        timeSigTable[sig][2] |= CHAR_DP;
    }

    for (int d = 0; d < 4; d++)
    {
        charOn[d] = true;
    }

    DEBUG_AND_WAIT("Exiting DisplayHandler Constructor", 1000);
}

void DisplayHandler::initialise()
{
    DEBUG_AND_WAIT("Init DisplayHandler", 1000);

    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    for (int i = 0; i < 4; i++)
    {
        pinMode(controlDigits[i], OUTPUT); digitalWrite(controlDigits[i], LOW);
    }
}

void DisplayHandler::refresh()
{
    displayInteger(this->lastNumber);
    delayMicroseconds(1638*((100-brightness)/10));
}

void DisplayHandler::setNumber(int number)
{    
    this->lastNumber = number;
}

void DisplayHandler::setTimeSignature(eTimeSignature sig)
{
    this->signature = sig;
}

void DisplayHandler::displayIntegerArray(int* intArray)
{
    int newInt = (intArray[0] * 100) + (intArray[1] * 10) + intArray[2];
    DEBUG_PRINTLN(newInt);
    setNumber(newInt);
}

void DisplayHandler::displayInteger(int integer)
{
    dd[3] = integer / 1000; integer %= 1000;
    dd[2] = integer / 100; integer %= 100;
    dd[1] = integer / 10; integer %= 10;
    dd[0] = integer;

    for(int x = 0; x < 3; x++)
    {
        for (int j = 0; j < 4; j++)
        {
            digitalWrite(controlDigits[j], LOW);    // turn off digits
        }

        digitalWrite(LATCH_PIN, LOW);

        if (charOn[2-x])
        {
            shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, charTable[dd[x]]);
        }
        else
        {
            shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CHAR_NULL);
        }

        digitalWrite(LATCH_PIN, HIGH);

        digitalWrite(controlDigits[x], HIGH);
        delay(1);
    }
    for (int j = 0; j < 4; j++)
    {
        digitalWrite(controlDigits[j], LOW);    // turn off digits
    }
}

void DisplayHandler::displayTimeSignature()
{
    int* sig = timeSigTable[this->signature];

    for(int x = 0; x < 4; x++)
    {
        for (int j = 0; j < 4; j++)
        {
            digitalWrite(controlDigits[j], LOW);    // turn off digits
        }

        digitalWrite(LATCH_PIN, LOW);

        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, sig[x]);

        digitalWrite(LATCH_PIN, HIGH);

        digitalWrite(controlDigits[x], HIGH);
        delay(1);
    }
    for (int j = 0; j < 4; j++)
    {
        digitalWrite(controlDigits[j], LOW);    // turn off digits
    }
}


void DisplayHandler::displayIdle()
{
    for(int x = 0; x < 4; x++)
    {
        for (int j = 0; j < 4; j++)
        {
            digitalWrite(controlDigits[j], LOW);    // turn off digits
        }

        digitalWrite(LATCH_PIN, LOW);

        shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, CHAR_MINUS);

        digitalWrite(LATCH_PIN, HIGH);

        digitalWrite(controlDigits[x], HIGH);
        delay(1);
    }
    for (int j = 0; j < 4; j++)
    {
        digitalWrite(controlDigits[j], LOW);    // turn off digits
    }
}

void DisplayHandler::toggleBlinking(int d)
{
    charOn[d] = !charOn[d];
}

void DisplayHandler::allOn()
{
    for (int d = 0; d < 4; d++)
    {
        charOn[d] = true;
    }
}