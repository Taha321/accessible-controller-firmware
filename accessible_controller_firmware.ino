#include "InputHandler.h"
#include "XInput.h"
#include "EventProcessor.h"
#include "MacroMiddleware.h"

EventProcessor eventProcessor;
MacroMiddleware macroMiddleware;

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  InputHandler::AddSubscriber(macroMiddleware);
  macroMiddleware.AddSubscriber(eventProcessor);
  Serial.print("Serial Mode");
}

void loop() 
{
  // Continuously pull off the Event Queue and process accordingly.
  eventProcessor.ProcessEvent();
}
