#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

#include "XInput.h"
#include "Event.h"
#include "KeyCode.h"
#include "Subscriber.h"
#include <eventqueue.h>

class EventProcessor : public Subscriber
{
    /*
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
public:
    EventProcessor();
    inline EventQueue<Event>& GetQueue() {return *m_Queue;}
    void OnEvent(Event e) override;
    void ProcessEvent();
private:
    EventQueue<Event>* m_Queue;
    //used to map firmware keyCodes to XInput enums for keys
private:
    static const uint8_t keyCodeMap[14];

};
#endif
