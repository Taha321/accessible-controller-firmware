#include "InputHandler.h"
#include <TeensyThreads.h>
#include "assert.h"
InputHandler* InputHandler::s_Instance = new InputHandler();

InputHandler::InputHandler()
{   
    assert(!s_Instance);
    int pins[] = {9,8,7,6,5,4,3,2,1,0,17,16,15,14,99,99};
    s_Instance = this;
    
    for (uint8_t i = 0; i < s_TotalInputs; i++) 
      s_Instance->m_PinAssignments[i] = pins[i];
    
    void (*ISR[])() = { ISR_PressA,ISR_PressB,ISR_PressX,ISR_PressY,ISR_PressRIGHT,ISR_PressLEFT,ISR_PressUP,ISR_PressDOWN,ISR_PressLT,ISR_PressRT,ISR_PressMacroRecording,ISR_PressMacro1 };
    for (uint8_t key = 0; key < s_NumButtons; key++)
    {
        pinMode(s_Instance->m_PinAssignments[key], INPUT);
        attachInterrupt(s_Instance->m_PinAssignments[key], ISR[key], RISING);
    }
    
    s_Instance->m_RightJoyStick.codeX = RightJoyStick_X;
    s_Instance->m_RightJoyStick.codeY = RightJoyStick_Y;

    s_Instance->m_LeftJoyStick.codeX = LeftJoyStick_X;
    s_Instance->m_LeftJoyStick.codeY = LeftJoyStick_Y;

    pinMode(s_Instance->m_PinAssignments[s_Instance->m_RightJoyStick.codeX], INPUT);
    pinMode(s_Instance->m_PinAssignments[s_Instance->m_RightJoyStick.codeY], INPUT);
    pinMode(s_Instance->m_PinAssignments[s_Instance->m_LeftJoyStick.codeX], INPUT);
    pinMode(s_Instance->m_PinAssignments[s_Instance->m_LeftJoyStick.codeY], INPUT);
    
    threads.addThread(TrackJoyStick, &s_Instance->m_RightJoyStick);
    threads.addThread(TrackJoyStick, &s_Instance->m_LeftJoyStick);
}

InputHandler::~InputHandler()
{
    for(uint8_t key = 0; key < s_NumButtons; key++)
      detachInterrupt(s_Instance->m_PinAssignments[key]);
    
    threads.kill(s_Instance->m_RightJoyStick.ThreadID);
    threads.kill(s_Instance->m_LeftJoyStick.ThreadID); 
}

void InputHandler::buttonPress(uint8_t keyCode)
{
    Event e;
    e.eventType = Event::Press;
    e.code = keyCode;
    if(s_Instance->m_EventCallback)
      s_Instance->m_EventCallback(e);
}

void InputHandler::buttonRelease(uint8_t keyCode)
{
    Event e;
    e.eventType = Event::Release;
    e.code = keyCode;
    if(s_Instance->m_EventCallback)
      s_Instance->m_EventCallback(e);
}

void InputHandler::TrackJoyStick(void* stick_Ptr)
{
    JoyStick* stick = (JoyStick*)stick_Ptr;
    stick->ThreadID = threads.id();
    
    while (true)
    {
        stick->x = analogRead(s_Instance->m_PinAssignments[stick->codeX])-32768;
        stick->y = analogRead(s_Instance->m_PinAssignments[stick->codeY])-32768;
    }
}

void InputHandler::ISR_PressMacroRecording() {
  buttonPress(keycode::Record_Macro);
}

static void InputHandler::ISR_PressMacro1() { buttonPress(Macro1); }

void InputHandler::ISR_PressA() { attachInterrupt(s_Instance->m_PinAssignments[key_A], ISR_ReleaseA, FALLING); buttonPress(key_A); }
void InputHandler::ISR_ReleaseA() { attachInterrupt(s_Instance->m_PinAssignments[key_A], ISR_PressA, RISING); buttonRelease(key_A); }
          
void InputHandler::ISR_PressB() { attachInterrupt(s_Instance->m_PinAssignments[key_B], ISR_ReleaseB, FALLING); buttonPress(key_B); }
void InputHandler::ISR_ReleaseB() { attachInterrupt(s_Instance->m_PinAssignments[key_B], ISR_PressB, RISING); buttonRelease(key_B); }
          
void InputHandler::ISR_PressX() { attachInterrupt(s_Instance->m_PinAssignments[key_X], ISR_ReleaseX, FALLING); buttonPress(key_X); }
void InputHandler::ISR_ReleaseX() { attachInterrupt(s_Instance->m_PinAssignments[key_X], ISR_PressX, RISING); buttonRelease(key_X); }
          
void InputHandler::ISR_PressY() { attachInterrupt(s_Instance->m_PinAssignments[key_Y], ISR_ReleaseY, FALLING); buttonPress(key_Y); }
void InputHandler::ISR_ReleaseY() { attachInterrupt(s_Instance->m_PinAssignments[key_Y], ISR_PressY, RISING); buttonRelease(key_Y); }
          
void InputHandler::ISR_PressRIGHT() { attachInterrupt(s_Instance->m_PinAssignments[Right], ISR_ReleaseRIGHT, FALLING); buttonPress(Right); }
void InputHandler::ISR_ReleaseRIGHT() { attachInterrupt(s_Instance->m_PinAssignments[Right], ISR_PressRIGHT, RISING); buttonRelease(Right); }
           
void InputHandler::ISR_PressLEFT() { attachInterrupt(s_Instance->m_PinAssignments[Left], ISR_ReleaseLEFT, FALLING); buttonPress(Left); }
void InputHandler::ISR_ReleaseLEFT() { attachInterrupt(s_Instance->m_PinAssignments[Left], ISR_PressLEFT, RISING); buttonRelease(Left); }
        
void InputHandler::ISR_PressUP() { attachInterrupt(s_Instance->m_PinAssignments[Up], ISR_ReleaseUP, FALLING); buttonPress(Up); }
void InputHandler::ISR_ReleaseUP() { attachInterrupt(s_Instance->m_PinAssignments[Up], ISR_PressUP, RISING); buttonRelease(Up); }
            
void InputHandler::ISR_PressDOWN() { attachInterrupt(s_Instance->m_PinAssignments[Down], ISR_ReleaseDOWN, FALLING); buttonPress(Down); }
void InputHandler::ISR_ReleaseDOWN() { attachInterrupt(s_Instance->m_PinAssignments[Down], ISR_PressDOWN, RISING); buttonRelease(Down); }
         
void InputHandler::ISR_PressLT() { attachInterrupt(s_Instance->m_PinAssignments[LT], ISR_ReleaseLT, FALLING); buttonPress(LT); }
void InputHandler::ISR_ReleaseLT() { attachInterrupt(s_Instance->m_PinAssignments[LT], ISR_PressLT, RISING); buttonRelease(LT); }
            
void InputHandler::ISR_PressRT() { attachInterrupt(s_Instance->m_PinAssignments[RT], ISR_ReleaseRT, FALLING); buttonPress(RT); }
void InputHandler::ISR_ReleaseRT() { attachInterrupt(s_Instance->m_PinAssignments[RT], ISR_PressRT, RISING); buttonRelease(RT); }
