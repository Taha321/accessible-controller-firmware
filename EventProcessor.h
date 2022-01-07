#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H
#include "XInput.h"


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

class EventProcessor 
{
    /* 
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
   public: 
    void begin(EventQueue<Event>& queue) 
    {
        EQ = queue;
    }
    
    // Event getEvent()
    // {
    //   Event e = {0};
    //   EQ->getQ(e)
    //   return e;
    // }    
    void ProcessEvent_XInput()
    {
      Event e;
      while(true)
      {
        if(EQ->getQ(e)) // Will return true if there is an event on the queue, false if it's empty
        {
          uint8_t code = mapping[e.code]; // Fetch mapping from private variable
          if e.type == Press 
            Xinput.press(code);

          else if e.type == Release 
            Xinput.release(code);
          
        }
      }
    }

    
   private: 
     static EventQueue<Event>* EQ;
     uint8_t mapping[] = {BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, DPAD_RIGHT, DPAD_LEFT, DPAD_UP, DPAD_DOWN, TRIGGER_LEFT, TRIGGER_RIGHT, JOY_LEFT, JOY_LEFT, JOY_RIGHT, JOY_RIGHT}

     

};
#endif
