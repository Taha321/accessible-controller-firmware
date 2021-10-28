#include "InputHandler.h"

InputHandler::InputHandler(EventQueue<Event>& queue)
{
    EQ = &queue;
    void (*ISR[])() = { ISR_PressA,ISR_PressB,ISR_PressX,ISR_PressY,ISR_PressRIGHT,ISR_PressLEFT,ISR_PressUP,ISR_PressDOWN,ISR_PressLT,ISR_PressRT };
    for (unsigned int key = 0; key < nKeys; key++)
    {
        pinMode(pinAssignments[key], INPUT_PULLDOWN);
        attachInterrupt(pinAssignments[key], ISR[key], RISING);
    }
}

InputHandler::InputHandler(EventQueue<Event>& queue, unsigned int* PinAssignments)
{
    for (unsigned int i = 0; i < nKeys; i++)
        pinAssignments[i] = PinAssignments[i];

    EQ = &queue;
    void (*ISR[])() = { ISR_PressA,ISR_PressB,ISR_PressX,ISR_PressY,ISR_PressRIGHT,ISR_PressLEFT,ISR_PressUP,ISR_PressDOWN,ISR_PressLT,ISR_PressRT };
    for (unsigned int key = 0; key < nKeys; key++)
    {
        pinMode(pinAssignments[key], INPUT_PULLDOWN);
        attachInterrupt(pinAssignments[key], ISR[key], RISING);
    }
}

void InputHandler::buttonPress(unsigned int keyCode)
{
    Event e;
    e.eventType = Event::Press;
    e.code = keyCode;
    if (EQ != nullptr)
        EQ->putQ(e);
}
void InputHandler::buttonRelease(unsigned int keyCode)
{
    Event e;
    e.eventType = Event::Release;
    e.code = keyCode;
    if (EQ != nullptr)
        EQ->putQ(e);
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

unsigned int InputHandler::pinAssignments[] = { 0,1,2,3,4,5,6,7,8,9 };      //Default pin assignments
EventQueue<Event>* InputHandler::EQ = nullptr;
