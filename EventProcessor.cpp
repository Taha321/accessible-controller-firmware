#include "EventProcessor.h"
#include "InputHandler.h"
#include "XInputAPI.h"

#include "assert.h"


static PlatformAPI* InitPlatformAPI()
{
  switch(PlatformAPI::Current())
  {
      case PlatformAPIType::XInput:
        return new XInputAPI(); 
        
      case PlatformAPIType::None:
        PlatformAPI::SetAPI(PlatformAPIType::XInput);
        return new XInputAPI(); 
      
      default:
        assert(false);
  }
}


EventProcessor::EventProcessor()
  :
  m_MacroProcessor(MacroProcessor())
{
  m_PlatformAPI = InitPlatformAPI();
}

EventProcessor::~EventProcessor()
{

}

void EventProcessor::OnUpdate() 
{
    Event e;
    if (InputHandler::GetEventQueue().getQ(e)) // Will return true if there is an event on the queue, false if it's empty
    {
      delay(e.wait); // member wait is 0 by default and some value if it is an event from a recorded macro
      m_MacroProcessor.DispatchEvent(e);
      m_PlatformAPI->DispatchEvent(e);
      if(e.Handled == false)          //Debugging
        Serial.println("EVENT NOT HANDLED");
  
    }
    m_PlatformAPI->SetJoyStick(JoyStickType::Right, InputHandler::GetRightAnalog().x, InputHandler::GetRightAnalog().y);
    m_PlatformAPI->SetJoyStick(JoyStickType::Left, InputHandler::GetLeftAnalog().x, InputHandler::GetLeftAnalog().y);
   
}
