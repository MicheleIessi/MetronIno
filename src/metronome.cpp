#include "metronome.hh"
#include "states/configTempoState.hh"
#include "states/workingState.hh"
#include "states/idleState.hh"
#include "utils.hh"

#include <Arduino.h>

Metronome::Metronome()
{
    currentTempo = new Tempo();
    MetronomeState* initialState = IdleState::getInstance();
    setState(initialState);
    initialised = true;
}

Tempo* Metronome::getCurrentTempo()
{
    return this->currentTempo;
}

void Metronome::setState(MetronomeState* newState)
{
    if (initialised)
    {       
        currentState->exit(this);
    }
    currentState = newState;
    currentState->enter(this);
}

void Metronome::performAction()
{
    currentState->act(this);
}