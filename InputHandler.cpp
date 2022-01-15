#include "InputHandler.h"
#include <TeensyThreads.h>

void InputHandler::begin(EventQueue<Event>& queue)
{   
    reset();  
    EQ = &queue;
    void (*ISR[])() = { ISR_PressA,ISR_PressB,ISR_PressX,ISR_PressY,ISR_PressRIGHT,ISR_PressLEFT,ISR_PressUP,ISR_PressDOWN,ISR_PressLT,ISR_PressRT };
    for (uint8_t key = 0; key < nButtons; key++)
    {
        pinMode(pinAssignments[key], INPUT);
        attachInterrupt(pinAssignments[key], ISR[key], RISING);
    }
    
    RightJoyStick.codeX = RightJoyStick_X;
    RightJoyStick.codeY = RightJoyStick_Y;

    LeftJoyStick.codeX = LeftJoyStick_X;
    LeftJoyStick.codeY = LeftJoyStick_Y;

    pinMode(pinAssignments[RightJoyStick.codeX], INPUT);
    pinMode(pinAssignments[RightJoyStick.codeY], INPUT);
    pinMode(pinAssignments[LeftJoyStick.codeX], INPUT);
    pinMode(pinAssignments[LeftJoyStick.codeY], INPUT);
    
    threads.addThread(TrackJoyStick, &RightJoyStick);
    threads.addThread(TrackJoyStick, &LeftJoyStick);
}

void InputHandler::begin(EventQueue<Event>& queue, uint8_t* Pins)
{
    reset();
    for (uint8_t i = 0; i < TotalInputs; i++)
        pinAssignments[i] = Pins[i];
        
    begin(queue);
}

void InputHandler::reset()
{
    for(uint8_t key = 0; key < nButtons; key++)
      detachInterrupt(pinAssignments[key]);
    
    threads.kill(RightJoyStick.ThreadID);
    threads.kill(LeftJoyStick.ThreadID); 
}

void InputHandler::buttonPress(uint8_t keyCode)
{
    Event e;
    e.eventType = Event::Press;
    e.code = keyCode;
    if (EQ != nullptr)
        EQ->putQ(e);
}

void InputHandler::buttonRelease(uint8_t keyCode)
{
    Event e;
    e.eventType = Event::Release;
    e.code = keyCode;
    if (EQ != nullptr)
        EQ->putQ(e);
}

JoyStick& InputHandler::RightAnalog(){ return RightJoyStick; }
JoyStick& InputHandler::LeftAnalog(){ return LeftJoyStick; }

void InputHandler::TrackJoyStick(void* stick_Ptr)
{
    JoyStick* stick = (JoyStick*)stick_Ptr;
    stick->ThreadID = threads.id();
    
    while (true)
    {
        stick->x = analogRead(pinAssignments[stick->codeX])-32768;
        stick->y = analogRead(pinAssignments[stick->codeY])-32768;
    }
}

void InputHandler::ISR_PressMacroRecording() {
  buttonPress(keycode::Record_Macro);
}

void InputHandler::ISR_PressA() { attachInterrupt(pinAssignments[key_A], ISR_ReleaseA, FALLING); buttonPress(key_A); }
void InputHandler::ISR_ReleaseA() { attachInterrupt(pinAssignments[key_A], ISR_PressA, RISING); buttonRelease(key_A); }
          
void InputHandler::ISR_PressB() { attachInterrupt(pinAssignments[key_B], ISR_ReleaseB, FALLING); buttonPress(key_B); }
void InputHandler::ISR_ReleaseB() { attachInterrupt(pinAssignments[key_B], ISR_PressB, RISING); buttonRelease(key_B); }
          
void InputHandler::ISR_PressX() { attachInterrupt(pinAssignments[key_X], ISR_ReleaseX, FALLING); buttonPress(key_X); }
void InputHandler::ISR_ReleaseX() { attachInterrupt(pinAssignments[key_X], ISR_PressX, RISING); buttonRelease(key_X); }
          
void InputHandler::ISR_PressY() { attachInterrupt(pinAssignments[key_Y], ISR_ReleaseY, FALLING); buttonPress(key_Y); }
void InputHandler::ISR_ReleaseY() { attachInterrupt(pinAssignments[key_Y], ISR_PressY, RISING); buttonRelease(key_Y); }
          
void InputHandler::ISR_PressRIGHT() { attachInterrupt(pinAssignments[Right], ISR_ReleaseRIGHT, FALLING); buttonPress(Right); }
void InputHandler::ISR_ReleaseRIGHT() { attachInterrupt(pinAssignments[Right], ISR_PressRIGHT, RISING); buttonRelease(Right); }
           
void InputHandler::ISR_PressLEFT() { attachInterrupt(pinAssignments[Left], ISR_ReleaseLEFT, FALLING); buttonPress(Left); }
void InputHandler::ISR_ReleaseLEFT() { attachInterrupt(pinAssignments[Left], ISR_PressLEFT, RISING); buttonRelease(Left); }
        
void InputHandler::ISR_PressUP() { attachInterrupt(pinAssignments[Up], ISR_ReleaseUP, FALLING); buttonPress(Up); }
void InputHandler::ISR_ReleaseUP() { attachInterrupt(pinAssignments[Up], ISR_PressUP, RISING); buttonRelease(Up); }
            
void InputHandler::ISR_PressDOWN() { attachInterrupt(pinAssignments[Down], ISR_ReleaseDOWN, FALLING); buttonPress(Down); }
void InputHandler::ISR_ReleaseDOWN() { attachInterrupt(pinAssignments[Down], ISR_PressDOWN, RISING); buttonRelease(Down); }
         
void InputHandler::ISR_PressLT() { attachInterrupt(pinAssignments[LT], ISR_ReleaseLT, FALLING); buttonPress(LT); }
void InputHandler::ISR_ReleaseLT() { attachInterrupt(pinAssignments[LT], ISR_PressLT, RISING); buttonRelease(LT); }
            
void InputHandler::ISR_PressRT() { attachInterrupt(pinAssignments[RT], ISR_ReleaseRT, FALLING); buttonPress(RT); }
void InputHandler::ISR_ReleaseRT() { attachInterrupt(pinAssignments[RT], ISR_PressRT, RISING); buttonRelease(RT); }

static void ISR_PressMacroRecording() { attachInterrupt(pinAssignments[Record_Macro], ISR_PressMacroRecording, FALLING); buttonRelease(Record_Macro)}
static void ISR_ReleaseMacroRecording() { attachInterrupt(pinAssignments[Record_Macro], ISR_ReleaseMacroRecording, RISING); buttonRelease(Record_Macro);}

static void ISR_PressMACRO1() { attachInterrupt(pinAssignments[Macro1],ISR_ReleaseMACRO1, FALLING); buttonPress(Macro1) }
static void ISR_ReleaseMACRO1() { attachInterrupt(pinAssignments[Macro1],ISR_ReleaseMACRO1, RISING); buttonPress(Macro1) };

uint8_t InputHandler::pinAssignments[] = { 0,1,2,3,4,5,6,7,8,9,10,11,14,15,16,17 };  //Default pin assignments
EventQueue<Event>* InputHandler::EQ = nullptr;

JoyStick InputHandler::LeftJoyStick = {0};
JoyStick InputHandler::RightJoyStick = {0};
