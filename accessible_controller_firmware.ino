#include "InputHandler.h"
#include "MacroProcessor.h"
#include "PlatformAPI.h"


MacroProcessor MacroProcessor();
PlatformAPI* PlatformAPI = InitPlatformAPI();

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  Serial.println("Serial Mode");
}

void loop() 
{
   if(!InputHandler::GetEventQueue().isEmpty())              // Will return true if there is an event on the queue, false if it's empty
   {
     Event e = InputHandler::GetEventQueue().dequeue();
     delay(e.wait);                                           // member wait is 0 by default and some value if it is an event from a recorded macro
     MacroProcessor.DispatchEvent(e);
     PlatformAPI->DispatchEvent(e);
   
     if(e.Handled == false)                                   //Debugging
       Serial.println("EVENT NOT HANDLED");
    }
    m_PlatformAPI->SetJoyStick(JoyStickType::Right, InputHandler::GetRightAnalog().x, InputHandler::GetRightAnalog().y);
    m_PlatformAPI->SetJoyStick(JoyStickType::Left, InputHandler::GetLeftAnalog().x, InputHandler::GetLeftAnalog().y);
}
