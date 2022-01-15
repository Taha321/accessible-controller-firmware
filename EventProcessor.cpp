#include "EventProcessor.h"
#include "InputHandler.h"
#include "assert.h"
EventProcessor* EventProcessor::s_Instance = nullptr;

EventProcessor::EventProcessor()
{
  assert(!s_Instance);
  s_Instance = this;
  m_Queue = new EventQueue<Event>();
}

void EventProcessor::ProcessEvent_XInput() 
{
    Event e;
    if (s_Instance->m_Queue->getQ(e)) // Will return true if there is an event on the queue, false if it's empty
    {
        uint8_t code = keyCodeMap[e.code]; // Fetch mapping from private variable
        
        bool handled = false;
        if (s_Instance->m_SubscriberCallbackFn)
          handled = s_Instance->m_SubscriberCallbackFn(e);
        
        if(!handled) 
        {
          if(e.eventType == Event::Press)
            XInput.press(code);

          else if(e.eventType == Event::Release)
            XInput.release(code); 
        }
    }
    XInput.setJoystick(JOY_RIGHT, InputHandler::GetRightAnalog().x, InputHandler::GetRightAnalog().y);
    XInput.setJoystick(JOY_LEFT, InputHandler::GetLeftAnalog().x, InputHandler::GetLeftAnalog().y);
}
const uint8_t EventProcessor::keyCodeMap[] = { BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, DPAD_RIGHT, DPAD_LEFT, DPAD_UP, DPAD_DOWN,
                                                TRIGGER_LEFT, TRIGGER_RIGHT, JOY_LEFT, JOY_LEFT, JOY_RIGHT, JOY_RIGHT }; 
