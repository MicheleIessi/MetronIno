#pragma once

#include <Arduino.h>

#ifdef DEBUG
    #ifdef SERIAL_PRINT
        #define DEBUG_PRINT(x)          Serial.print(x)
        #define DEBUG_PRINTLN(x)        Serial.println(x)
    #else
        #define DEBUG_PRINT(x)          printf("%s", x);
        #define DEBUG_PRINTLN(x)        printf("%s\n", x);
    #endif
    #define DEBUG_AND_WAIT(x, y)    DEBUG_PRINTLN(x); delay(y)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
    #define DEBUG_AND_WAIT(x, y)
#endif