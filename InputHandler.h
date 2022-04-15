#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include <Arduino.h>

#include "Event.h"
#include "KeyCode.h"
#include "Queue.h"


enum class JoyStickType 
{
    None = 0,
    Left,
    Right
};

struct JoyStick // Used to keep track of analogue inputs
{
    int ThreadID;
    uint8_t codeX;
    uint8_t codeY;
    int16_t x;
    int16_t y;
};

using OnEventCallbackFn = void (*)(Event);
class InputHandler
{
  //keyCode enums and Event struct definition found in EventProcessor.h
  public:
      InputHandler();
      virtual ~InputHandler();
      
      static void buttonPress(uint8_t keyCode);                             //Button Press event generated and added to queue for a given keyCode
      static void buttonRelease(uint8_t keyCode);                           //Button Release event generated and added to queue for a given keyCode
      
      static inline void setEventCallbackFn(OnEventCallbackFn callback) {s_Instance->m_EventCallback = callback;}
      
      static inline const JoyStick& GetRightAnalog() { return s_Instance->m_RightJoyStick; }                                      
      static inline const JoyStick& GetLeftAnalog() { return s_Instance->m_LeftJoyStick; }

      static inline Queue<Event>& GetEventQueue(){ return s_EventQueue; }
      
  private:
      static void TrackJoyStick(void* stick_Ptr); 

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
      
      static void ISR_PressMacroRecording();                                //ISR for event, Press Record_Macro
      
      static void ISR_PressMacro1();                                        //ISR for event, Press Macro1

  private:
      static constexpr uint8_t s_TotalInputs = 16;
      static constexpr uint8_t s_NumButtons = 12;                           //Number of implemented inputs
      static constexpr uint8_t s_NumAnalog = 4;

      static Queue<Event> s_EventQueue;
      static InputHandler* s_Instance;
      
  private:
      OnEventCallbackFn m_EventCallback = NULL;
      uint8_t m_PinAssignments[s_TotalInputs];
      
      JoyStick m_LeftJoyStick;                                            //Holds information about the current state of Left Joystick
      JoyStick m_RightJoyStick;                                           //Holds information about the current state of Right Joystick 
};


#endif
