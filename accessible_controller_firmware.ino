#include "InputHandler.h"

EventQueue<Event> q; 
InputHandler IH(q);

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  Serial.begin(9600);
}
int i=0;
void loop() 
{
  Event e;
  if(q.getQ(e))
  {
    if(e.eventType == Event::Press)
    {
      digitalWrite(14,HIGH);
      Serial.print("button presses = ");
      Serial.print(i);
      Serial.print("\tKeyCode: ");
      Serial.print(e.code);
      Serial.println("\tEvent: Press!");
      //Serial.println(q.nThreads);
      i++;
      
    }
    else if(e.eventType == Event::Release)
    {
      digitalWrite(14,LOW);
      Serial.print("\t\t\tKeyCode: ");
      Serial.print(e.code);
      Serial.println("\tEvent: Release!");
      //Serial.println(q.nThreads);
    }
  }
}
