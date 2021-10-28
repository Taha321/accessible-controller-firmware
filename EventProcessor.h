#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H


enum keycode
{
    key_A = 0, key_B = 1, key_X = 2, key_Y = 3,
    Right = 4, Left = 5, Up = 6, Down = 7,
    LT = 8, RT = 9
};
struct Event
{
    enum type
    {
        Press,
        Release
    };
    type eventType;
    unsigned int code;
};


#endif
