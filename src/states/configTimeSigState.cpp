#include "states/configTimeSigState.hh"
#include "states/workingState.hh"
#include "inputs/inputHandler.hh"
#include "display/displayHandler.hh"
#include "utils.hh"

void ConfigTimeSigState::enter(Metronome* m)
{
    DEBUG_PRINTLN("ConfigTempoState");
    currentSig = DEFAULT_TIME_SIGNATURE;
    DisplayHandler::getInstance()->setTimeSignature(currentSig);
    DisplayHandler::getInstance()->displayTimeSignature();
}

void ConfigTimeSigState::act(Metronome* m)
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
            currentSig = (eTimeSignature)((currentSig + 1 ) % TIME_SIG_NUMBER);
            DisplayHandler::getInstance()->setTimeSignature(currentSig);
            break;
        case CMD_BUTTON_DOWN:
            currentSig = (eTimeSignature)((currentSig + (TIME_SIG_NUMBER - 1) ) % TIME_SIG_NUMBER);
            DisplayHandler::getInstance()->setTimeSignature(currentSig);
            break;
        case CMD_BUTTON_CHANGE:
            // DEBUG_PRINT("current digit: "); DEBUG_PRINTLN(this->currentDigit);
            m->getCurrentTempo()->setTimeSignature(currentSig);
            m->setState(this->nextState());        
        default:
            break;
        }
    }
    DisplayHandler::getInstance()->displayTimeSignature();
}

void ConfigTimeSigState::exit(Metronome* m)
{

}

MetronomeState* ConfigTimeSigState::nextState()
{
    return WorkingState::getInstance();
}