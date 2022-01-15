#pragma once

struct Event // represents a button press/release 
{
    enum type
    {
        Press,
        Release,
    };
    type eventType;
    uint8_t code;
    bool Handled = false;
};
