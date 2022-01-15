#include "InputHandler.h"
#include "XInput.h"
#include "EventProcessor.h"
#include "MacroProcessor.h"

EventProcessor eventProcessor;
MacroProcessor macroProcessor;

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  InputHandler::AddSubscriber(macroProcessor);
  InputHandler::AddSubscriber(eventProcessor);
  macroProcessor.AddSubscriber(eventProcessor);
  Serial.print("Serial Mode");
}

void loop() 
{
  // Continuously pull off the Event Queue and process accordingly.
  eventProcessor.ProcessEvent();
}
