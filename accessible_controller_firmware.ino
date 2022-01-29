#include "InputHandler.h"
#include "EventProcessor.h"



EventProcessor eventProcessor;


void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  Serial.println("Serial Mode");
}

void loop() 
{
  // Continuously pull off the Event Queue and process accordingly.
  eventProcessor.OnUpdate();
}
