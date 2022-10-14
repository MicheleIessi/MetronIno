#pragma once

#define COMMAND_QUEUE_SIZE  16

#include <Arduino.h>
#include "inputs/commands.h"

class InputHandler
{
public:
    void initialise();
    CommandQueue* getCommandQueue();

    void handleInputs();
    void setCmdStatus(eCommand cmd, bool status);
    void resetCmdStatus(eCommand cmd);

    static InputHandler* getInstance() {
        static InputHandler instance;
        return &instance;
    }


private:
    InputHandler();
    
    CommandQueue* queue;
    bool cmdStatus[NUMBER_OF_COMMANDS];
    char prevStatus[NUMBER_OF_COMMANDS];
    char pinTable[NUMBER_OF_COMMANDS];
};