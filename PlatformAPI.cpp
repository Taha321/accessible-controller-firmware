#include "PlatformAPI.h"

void PlatformAPI::DispatchEvent(Event& e)
{
  if(e.Handled == false)
  {
    if(e.eventType == Event::Press)
    {
       Serial.print("Press ");  //Debugging
       Serial.println(e.code);  //Debugging
       Press(e.code);
    }
    else if(e.eventType == Event::Release)
    {
       Serial.print("Release ");  //Debugging
       Serial.println(e.code);    //Debugging
       Release(e.code);
    }
    e.Handled = true;
  }
}

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

PlatformAPIType PlatformAPI::s_CurrentAPI = PlatformAPIType::None;
