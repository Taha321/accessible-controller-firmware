#include "InputHandler.h"
#include "XInput.h"

EventQueue<Event> q; 
uint8_t pins[] = {9,8,7,6,5,4,3,2,1,0,17,16,15,14};

void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  analogReadResolution(16);
  IH.begin(q, pins);
}

int i=0;
void loop() 
{
  //XInput.setJoystick(JOY_RIGHT , IH.RightAnalog().x, IH.RightAnalog().y);
  //XInput.setJoystick(JOY_LEFT , IH.LeftAnalog().x, IH.LeftAnalog().y);
  
  Event e;
  if(q.getQ(e))
  {
    if(e.eventType == Event::Press)
    {
      digitalWrite(13,HIGH);
      if((e.code == LT))
      {
          
        Serial.print("Right JoyStick = ");
        Serial.print(IH.RightAnalog().x);
        Serial.print(", ");
        Serial.println(IH.RightAnalog().y);
    
        Serial.print("Left JoyStick = ");
        Serial.print(IH.LeftAnalog().x);
        Serial.print(", ");
        Serial.println(IH.LeftAnalog().y);
        Serial.println();
      }
      else
      {
        Serial.print("button presses = ");
        Serial.print(i);
        Serial.print("\tKeyCode: ");
        Serial.print(e.code);
        Serial.println("\tEvent: Press!");
        //Serial.println(q.nThreads);
        i++;
      } 
    }
    else if(e.eventType == Event::Release)
    {
      digitalWrite(13,LOW);
      if(!(e.code == LT))
      {
        Serial.print("\t\t\tKeyCode: ");
        Serial.print(e.code);
        Serial.println("\tEvent: Release!");
        //Serial.println(q.nThreads);
      }
    }
  }
}
