#include "states/configTempoState.hh"
#include "states/ConfigTimeSigState.hh"
#include "inputs/inputHandler.hh"
#include "display/displayHandler.hh"
#include "utils.hh"

void ConfigTempoState::resetTempo(Tempo* tempo)
{
    tempo->setBPM(DEFAULT_BPM);
    tempo->setTimeSignature(DEFAULT_TIME_SIGNATURE);
    this->digits[0] = DEFAULT_BPM / 100;
    this->digits[1] = (DEFAULT_BPM % 100) / 10;
    this->digits[2] = DEFAULT_BPM % 10;
    DisplayHandler::getInstance()->displayIntegerArray(this->digits);
}

void ConfigTempoState::enter(Metronome* m)
{
    DEBUG_PRINTLN("ConfigTempoState");
    resetTempo(m->getCurrentTempo());
}

void ConfigTempoState::act(Metronome* m)
{
    InputHandler* handler = InputHandler::getInstance();
    eCommand cmd;
    bool request = handler->getCommandQueue()->pop(&cmd);
    int mod = (this->currentDigit == 0) ? 4 : 10;
    static unsigned int lastBlink = millis();

    if (request)
    {
        DisplayHandler::getInstance()->allOn();
        lastBlink = millis();       // Postpone blinking
        // Handle the relevant request
        switch (cmd)
        {
        case CMD_BUTTON_UP:
            this->digits[currentDigit] = (this->digits[currentDigit] + 1) % mod;
            break;
        case CMD_BUTTON_DOWN:
            this->digits[currentDigit] = (this->digits[currentDigit] + mod - 1) % mod;
            break;
        case CMD_BUTTON_CHANGE:
            if (this->currentDigit == LAST_DIGIT)
            {
                this->currentDigit = FIRST_DIGIT;
                // Set new tempo
                m->getCurrentTempo()->setBPMFromArray(this->digits);                
                m->setState(this->nextState());
            }
            else
            {
                this->currentDigit = (eDigit)(this->currentDigit + 1);
            }
            break;
        
        default:
            break;
        }
        DisplayHandler::getInstance()->displayIntegerArray(this->digits);
    }

    if (millis() > (lastBlink + BLINKING_TIME))
    {
        DisplayHandler::getInstance()->toggleBlinking(this->currentDigit);
        lastBlink = millis();
    }
    DisplayHandler::getInstance()->refresh();
}

void ConfigTempoState::exit(Metronome* m)
{
    DisplayHandler::getInstance()->allOn();
    DisplayHandler::getInstance()->setNumber(m->getCurrentTempo()->getBPM());
}

MetronomeState* ConfigTempoState::nextState()
{
    return ConfigTimeSigState::getInstance();
}