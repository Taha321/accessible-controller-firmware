#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

enum keycode : uint8_t
{
    key_A = 0, 
    key_B = 1, 
    key_X = 2, 
    key_Y = 3,
    Right = 4, 
    Left = 5, 
    Up = 6, 
    Down = 7,
    LT = 8, 
    RT = 9, 
    RightJoyStick_X = 10, 
    RightJoyStick_Y = 11,
    LeftJoyStick_X = 12, 
    LeftJoyStick_Y = 13
};
struct Event
{
    enum type
    {
        Press,
        Release
    };
    type eventType;
    uint8_t code;
};

struct JoyStick
{
    int ThreadID;
    uint8_t codeX;
    uint8_t codeY;
    uint16_t x;
    uint16_t y;
};


#endif
