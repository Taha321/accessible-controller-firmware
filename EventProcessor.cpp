#include "EventProcessor.h"


void EventProcessor::begin(EventQueue<Event>& queue)
{
  EQ = &queue;
}

void EventProcessor::ProcessEvent_XInput() 
{
    Event e;
    if (EQ->getQ(e)) // Will return true if there is an event on the queue, false if it's empty
    {
        uint8_t code = keyCodeMap[e.code]; // Fetch mapping from private variable
        if(e.eventType == Event::Press)
            XInput.press(code);

        else if(e.eventType == Event::Release)
            XInput.release(code);
    }
    XInput.setJoystick(JOY_RIGHT, IH.RightAnalog().x, IH.RightAnalog().y);
    XInput.setJoystick(JOY_LEFT, IH.LeftAnalog().x, IH.LeftAnalog().y);
}

EventQueue<Event>* EventProcessor::EQ = nullptr;
const uint8_t EventProcessor::keyCodeMap[] = { BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, DPAD_RIGHT, DPAD_LEFT, DPAD_UP, DPAD_DOWN,
                                              TRIGGER_LEFT, TRIGGER_RIGHT, JOY_LEFT, JOY_LEFT, JOY_RIGHT, JOY_RIGHT }; 
