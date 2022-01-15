#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include <Arduino.h>
#include <eventqueue.h>



enum keycode : uint8_t // keyCode enums used to refer to different keys of a controller
{
    key_A = 0,
    key_B = 1, 
    key_X = 2, 
    key_Y = 3,
    Right = 4, 
    Left = 5, 
    Up = 6, 
    Down = 7,
    LT = 8, 
    RT = 9,
    Record_Macro = 10,
    Macro1 = 11,
    RightJoyStick_X = 12, 
    RightJoyStick_Y = 13,
    LeftJoyStick_X = 14, 
    LeftJoyStick_Y = 15
};
/*
enum class EventType
{
  None = 0,
  ButtonPressed,
  ButtonReleased
};
*/

struct Event // represents a button press/release 
{
    enum type
    {
        Press,
        Release
    };
    type eventType;
    uint8_t code;
    bool Handled = false;
};

struct JoyStick // Used to keep track of analogue inputs
{
    int ThreadID;
    uint8_t codeX;
    uint8_t codeY;
    int16_t x;
    int16_t y;
};


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

      static JoyStick& RightAnalog();                                       //Get read-only access to the Right analog Stick
      static JoyStick& LeftAnalog();                                        //Get read-only access to the Left analog Stick

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
      
      static void ISR_PressMacroRecording();
      static void ISR_ReleaseMacroRecording();
      
      static void ISR_PressMACRO1();
      static void ISR_ReleaseMACRO1();

  private:      
      static constexpr uint8_t TotalInputs = 16;
      static constexpr uint8_t nButtons = 13;                               //Number of implemented inputs
      static constexpr uint8_t nAnalog = 4;
  
      static JoyStick LeftJoyStick;                                         //Holds information about the current state of Left Joystick
      static JoyStick RightJoyStick;                                        //Holds information about the current state of Right Joystick
            
      static EventQueue<Event>* EQ;                                         //Pointer to the targetted event queue    
      static uint8_t pinAssignments[TotalInputs];                           //Pin assignments, indexed by keycode enums, default pin assignments found in InputHandler.cpp
};

extern InputHandler IH;                                                     //Global InputHandler class instance
#endif
