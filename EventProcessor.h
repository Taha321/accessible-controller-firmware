#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

#include "XInput.h"
#include "Event.h"
#include "KeyCode.h"
#include <eventqueue.h>

using SubscriberCallbackFn = bool (*)(Event);

class EventProcessor
{
    /*
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
public:
    EventProcessor();
    inline EventQueue<Event>& GetQueue() {return *m_Queue;}
public:
    static inline EventProcessor& Get() {return *s_Instance; }
    static void ProcessEvent_XInput();
    static void ProcessEvent_Switch();
    static inline void SetSubscriberCallbackFn(SubscriberCallbackFn callback) {s_Instance->m_SubscriberCallbackFn = callback;}
private:
    EventQueue<Event>* m_Queue;
    SubscriberCallbackFn m_SubscriberCallbackFn;
    //used to map firmware keyCodes to XInput enums for keys
private:
    static const uint8_t keyCodeMap[14];
    static EventProcessor* s_Instance;
};
#endif
