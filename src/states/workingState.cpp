#include "states/workingState.hh"
#include "states/idleState.hh"
#include "inputs/inputHandler.hh"
#include "display/displayHandler.hh"
#include "utils.hh"
#include "toneHandler.hh"
#include "pins.hh"

#include <Arduino.h>

static char val = 0;
Tempo* workingTempo;

void WorkingState::enter(Metronome* m)
{
    DEBUG_PRINTLN("Entering WorkingState");
    // Set up timer
    workingTempo = m->getCurrentTempo();
    workingTempo->setBeat(0);
    DEBUG_PRINT("Current BPM: "); DEBUG_PRINTLN(workingTempo->getBPM());
    DisplayHandler::getInstance()->setNumber(workingTempo->getBPM());

    /** Timer1 setup */
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << CS12);
    TCCR1B |= (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = BPM_TO_FREQ(workingTempo->getBPM());
    interrupts();
}

void WorkingState::act(Metronome* m)
{
    InputHandler* handler = InputHandler::getInstance();
    eCommand cmd;
    bool request = handler->getCommandQueue()->pop(&cmd);

    if (request)
    {
        // Handle the relevant request
        switch (cmd)
        {
        case CMD_BUTTON_UP:
            noInterrupts();
            workingTempo->setBPM(workingTempo->getBPM() + 1);
            OCR1A = BPM_TO_FREQ(workingTempo->getBPM());
            interrupts();
            break;
        case CMD_BUTTON_DOWN:
            noInterrupts();
            workingTempo->setBPM(workingTempo->getBPM() - 1);
            OCR1A = BPM_TO_FREQ(workingTempo->getBPM());
            interrupts();
            break;
        case CMD_BUTTON_CHANGE:
            m->setState(this->nextState());
            break;
        default:
            DEBUG_PRINT("Invalid request: "); DEBUG_PRINTLN(cmd);
            break;
        }
        DisplayHandler::getInstance()->setNumber(workingTempo->getBPM());
    }
    DisplayHandler::getInstance()->refresh();
}

void WorkingState::exit(Metronome* m)
{
    DEBUG_PRINTLN("Exiting working state");
    TIMSK1 = (0 << OCIE1A);
    val = 0;
    digitalWrite(LED_BUILTIN, LOW);
}


MetronomeState* WorkingState::nextState()
{
    return IdleState::getInstance();  // replace with idle state
}

ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0;
    val = ~val;
    ToneHandler::getInstance()->generateTone();
    workingTempo->incrementBeat();
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
}