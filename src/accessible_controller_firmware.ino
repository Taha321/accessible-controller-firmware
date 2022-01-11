#include "InputHandler.h"
#include "XInput.h"
#include "EventProcessor.h"

EventQueue<Event> q; 
uint8_t pins[] = {9,8,7,6,5,4,3,2,1,0,17,16,15,14};

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  IH.begin(q, pins);
  EP.begin(q);
  Serial.print("Serial Mode");
}

void loop() 
{
  // Continuously pull off the Event Queue and process accordingly.
  EP.ProcessEvent_XInput();
}
