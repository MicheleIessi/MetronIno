#include "inputs/commands.h"
#include "utils.hh"

#include <Arduino.h>

CommandQueue::CommandQueue()
{
    this->elems = 0;
}

bool CommandQueue::isEmpty()
{
    return (this->elems == 0);
}

bool CommandQueue::isFull()
{
    return (this->elems == COMMAND_QUEUE_SIZE);
}

bool CommandQueue::pop(eCommand* cmd)
{
    bool retVal = false;
    if (!this->isEmpty())
    {
        *cmd = this->queue[elems];
        elems -= 1;
        retVal = true;
    }
    return retVal;
}

bool CommandQueue::push(eCommand cmd)
{
    bool retVal = false;
    if (!this->isFull())
    {
        this->queue[++elems] = cmd;
        retVal = true;
    }
    return retVal;
}