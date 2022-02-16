#pragma once
#include <stdint.h>

struct Event // represents a button press/release 
{
    enum type : uint8_t
    {
        Press,
        Release
    };
    type eventType;
    uint8_t code;
    uint16_t wait = 0; 
    bool Handled = false;
};
