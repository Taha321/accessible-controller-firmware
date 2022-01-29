#pragma once
#include <stdint.h>

struct Event // represents a button press/release 
{
    enum type
    {
        Press,
        Release,
    };
    type eventType;
    uint8_t code;
    unsigned long wait = 0; 
    bool Handled = false;
};
