#include "states/idleState.hh"
#include "states/configTempoState.hh"
#include "inputs/inputHandler.hh"
#include "display/displayHandler.hh"
#include "utils.hh"

void IdleState::enter(Metronome* m)
{
    DEBUG_PRINTLN("Entering IdleState");
}

void IdleState::act(Metronome* m)
{
    InputHandler* handler = InputHandler::getInstance();
    eCommand cmd;
    bool request = handler->getCommandQueue()->pop(&cmd);

    if (request)
    {
        // Do nothing
        switch (cmd)
        {
        case CMD_BUTTON_UP:
        case CMD_BUTTON_DOWN:
        case CMD_BUTTON_CHANGE:
            m->setState(this->nextState());
            break;
        default:
            break;
        }
    }
    DisplayHandler::getInstance()->displayIdle();
}

void IdleState::exit(Metronome* m)
{
    // Do nothing
}


MetronomeState* IdleState::nextState()
{
    return ConfigTempoState::getInstance();
}