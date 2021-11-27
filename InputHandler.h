#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include <Arduino.h>
#include <eventqueue.h>

#include "EventProcessor.h"

class InputHandler
{
  //keyCode enums and Event struct definition found in EventProcessor.h

  public:
      InputHandler() = delete;                                              //Static class, therefore can not be instantiated
      InputHandler(const InputHandler&) = delete;                           
      InputHandler& operator=(const InputHandler&) = delete;

      static void begin(EventQueue<Event>& queue);                          //Reference to the target event queue stored in EQ, all ISR attached to default input pins
      static void begin(EventQueue<Event>& queue, uint8_t* Pins);           //In addition to the first begin() function, an array of pin numbers is used to change pin assignments for inputs 
      static void reset();
      
      static void buttonPress(uint8_t keyCode);                             //Button Press event generated and added to queue for a given keyCode
      static void buttonRelease(uint8_t keyCode);                           //Button Release event generated and added to queue for a given keyCode

      static const JoyStick& RightAnalog();                                 //Get read-only access to the Right analog Stick
      static const JoyStick& LeftAnalog();                                  //Get read-only access to the Left analog Stick

  private:
  
      static void TrackJoyStick(void* stick_Ptr);                           //Track JoyStick values     


      //ISR for individual key interrupts created, using the buttonPress and buttonRelease methods


      static void ISR_PressA();                                             //ISR for event, Press A
      static void ISR_ReleaseA();                                           //ISR for event, Release A
                                                                                           
      static void ISR_PressB();                                             //ISR for event, Press B
      static void ISR_ReleaseB();                                           //ISR for event, Release B
                                                                                           
      static void ISR_PressX();                                             //ISR for event, Press X
      static void ISR_ReleaseX();                                           //ISR for event, Release X
                                                                                           
      static void ISR_PressY();                                             //ISR for event, Press Y
      static void ISR_ReleaseY();                                           //ISR for event, Release Y
                                                                                           
      static void ISR_PressRIGHT();                                         //ISR for event, Press Right
      static void ISR_ReleaseRIGHT();                                       //ISR for event, Release Right
                                                                                           
      static void ISR_PressLEFT();                                          //ISR for event, Press Left
      static void ISR_ReleaseLEFT();                                        //ISR for event, Release Left
                                                                                           
      static void ISR_PressUP();                                            //ISR for event, Press Up
      static void ISR_ReleaseUP();                                          //ISR for event, Release Up
                                                                                           
      static void ISR_PressDOWN();                                          //ISR for event, Press Down
      static void ISR_ReleaseDOWN();                                        //ISR for event, Release Down
                                                                                           
      static void ISR_PressLT();                                            //ISR for event, Press LT
      static void ISR_ReleaseLT();                                          //ISR for event, Release LT
                                                                                           
      static void ISR_PressRT();                                            //ISR for event, Press RT
      static void ISR_ReleaseRT();                                          //ISR for event, Release RT

  private:      
      static constexpr uint8_t TotalInputs = 14;
      static constexpr uint8_t nButtons = 10;                               //Number of implemented inputs
      static constexpr uint8_t nAnalog = 4;
  
      static JoyStick LeftJoyStick;                                         //Holds information about the current state of Left Joystick
      static JoyStick RightJoyStick;                                        //Holds information about the current state of Right Joystick
            
      static EventQueue<Event>* EQ;                                         //Pointer to the targetted event queue    
      static uint8_t pinAssignments[TotalInputs];                           //Pin assignments, indexed by keycode enums, default pin assignments found in InputHandler.cpp
};

extern InputHandler IH;                                                     //Global InputHandler class instance
#endif
