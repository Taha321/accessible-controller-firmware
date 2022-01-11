#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

#include "XInput.h"
#include "InputHandler.h"

class EventProcessor
{
    /*
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
public:
    EventProcessor() = delete;
    EventProcessor(const EventProcessor&) = delete;
    EventProcessor& operator= (const EventProcessor&) = delete;

    static void begin(EventQueue<Event>& queue);
    static void ProcessEvent_XInput();
    
private:
    static EventQueue<Event>* EQ;

    //used to map firmware keyCodes to XInput enums for keys
    static const uint8_t keyCodeMap[14];
};
extern EventProcessor EP;
#endif
