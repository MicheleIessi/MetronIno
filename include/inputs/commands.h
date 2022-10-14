#pragma once

#define COMMAND_QUEUE_SIZE  16

#define NUMBER_OF_COMMANDS CMD_INVALID
#define IS_VALID(cmd)   ((cmd >= CMD_FIRST_COMMAND) && (cmd <= CMD_LAST_COMMAND)) || (cmd == CMD_ALL)
typedef enum
{
    CMD_FIRST_COMMAND,
    CMD_BUTTON_UP = CMD_FIRST_COMMAND,
    CMD_BUTTON_DOWN,
    CMD_BUTTON_CHANGE,
    CMD_INVALID,
    CMD_LAST_COMMAND = CMD_INVALID - 1,
    CMD_ALL
} eCommand;

class CommandQueue
{
public:
    bool push(eCommand cmd);
    bool pop(eCommand* cmd);
    bool isEmpty();
    bool isFull();

    CommandQueue();

private:
    eCommand    queue[COMMAND_QUEUE_SIZE];
    int         elems;
};