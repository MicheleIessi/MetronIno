#include "inputs/inputHandler.hh"
#include "utils.hh"
#include "pins.hh"

InputHandler::InputHandler()
{
    this->queue = new CommandQueue();
    memset(cmdStatus, 0, sizeof(cmdStatus));
    memset(prevStatus, 0, sizeof(prevStatus));
    pinTable[CMD_BUTTON_CHANGE] = CHANGE_STATUS_PIN;
    pinTable[CMD_BUTTON_DOWN] = DOWN_PIN;
    pinTable[CMD_BUTTON_UP] = UP_PIN;
}

void InputHandler::initialise()
{
    DEBUG_PRINTLN("Initialising InputHandler");
    
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(SOUND_PIN, OUTPUT);

    digitalWrite(SOUND_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
}

CommandQueue* InputHandler::getCommandQueue()
{
    return this->queue;
}

void InputHandler::handleInputs()
{
    for (int c = CMD_FIRST_COMMAND; c <= CMD_LAST_COMMAND; c++)
    {
        if ((!cmdStatus[c]) && (HIGH == digitalRead(pinTable[c])))
        {
            //DEBUG_PRINT("Pressed "); DEBUG_PRINTLN(c);
            prevStatus[c] = HIGH;
            setCmdStatus((eCommand) c, true);
            queue->push((eCommand) c);
        }
    }
}

void InputHandler::setCmdStatus(eCommand cmd, bool status)
{
    if ((IS_VALID(cmd)) && (CMD_ALL != cmd))
    {
        cmdStatus[cmd] = status;
    }
}

void InputHandler::resetCmdStatus(eCommand cmd)
{
    if (IS_VALID(cmd))
    {
        if (CMD_ALL == cmd)
        {
            /** Check if status were high and are now low */
            for (int c = CMD_FIRST_COMMAND; c <= CMD_LAST_COMMAND; c++)
            {
                if (digitalRead(pinTable[c]) == LOW)
                {
                    cmdStatus[c] = digitalRead(pinTable[c]);
                }
            }
        }
        else
        {
            cmdStatus[cmd] = false;
        }
    }
}
