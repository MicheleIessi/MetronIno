#include <Arduino.h>
#include "metronome.hh"
#include "inputs/inputHandler.hh"
#include "toneHandler.hh"
#include "display/displayHandler.hh"
#include "utils.hh"

Metronome*      m;
InputHandler*   inputHandler;
ToneHandler*    toneHandler;
DisplayHandler* displayHandler;
int i;

void setup()
{
#ifdef DEBUG
    #ifdef SERIAL_PRINT
        Serial.begin(9600);
    #endif
#endif
    inputHandler = InputHandler::getInstance();
    inputHandler->initialise();

    toneHandler = ToneHandler::getInstance();

    m = new Metronome();

    toneHandler->setMetronome(m);
    toneHandler->testTones();

    displayHandler = DisplayHandler::getInstance();
    displayHandler->initialise();

    i = 0;
}


void loop()
{
    //DEBUG_PRINT("LOOP "); DEBUG_PRINTLN(i++);
    /** Reset input states */
    inputHandler->resetCmdStatus(CMD_ALL);
    /** Handle input (e.g. a request to change the current state) */
    inputHandler->handleInputs();
    /** Perform actions according to the current state */
    m->performAction();
}
