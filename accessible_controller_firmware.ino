#include "InputHandler.h"
#include "XInput.h"
#include "EventProcessor.h"
#include "MacroProcessor.h"

EventProcessor eventProcessor;
MacroProcessor macroProcessor;

void onEvent(Event e) {
  eventProcessor.GetQueue().putQ(e);
}

bool subscribe(Event e) {
  bool handled = MacroProcessor::OnEvent(e);
  return handled;
}

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  InputHandler::setEventCallbackFn(onEvent);
  eventProcessor.SetSubscriberCallbackFn(subscribe);
  Serial.print("Serial Mode");
}

void loop() 
{
  // Continuously pull off the Event Queue and process accordingly.
  eventProcessor.ProcessEvent_XInput();
}
