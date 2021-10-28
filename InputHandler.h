#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H


#include <Arduino.h>
#include <eventqueue.h>
#include <TeensyThreads.h>

#include "EventProcessor.h"



class InputHandler
{
  //keyCode enums and Event struct definition found in EventProcessor.h

  public:
      InputHandler() = delete;
      InputHandler(EventQueue<Event>& queue);                               //During initialization, a reference to an EventQueue to be used by the InputHandler is also provided
                                                                            //The constructor also attaches ISR to their corresponding key Interrupts based on the default pin assignments

      InputHandler(EventQueue<Event>& queue, unsigned int* PinAssignments); //In addition to functionality of the first constructor, custom pins are also assigned to keys
                                                                            //PinAssignments is indexed by keyCodes

      InputHandler(const InputHandler&) = delete;                           //Copy constructor and copy assignment can not be used
      InputHandler& operator=(const InputHandler&) = delete;

      static void buttonPress(unsigned int keyCode);                        //Button Press event generated and added to queue for a given keyCode
      static void buttonRelease(unsigned int keyCode);                      //Button Release event generated and added to queue for a given keyCode

  private:
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
      static EventQueue<Event>* EQ;                                         //Pointer to an event queue 
      static constexpr unsigned int nKeys = 10;                             //Number of keys implemented      
      static unsigned int pinAssignments[nKeys];                            //Pin assignments, indexed by keyCodes, Default pin assignments found in InputHandler.cpp
};


#endif
