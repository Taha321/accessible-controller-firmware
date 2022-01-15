#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

#include "Event.h"
#include "KeyCode.h"
#include "Subscriber.h"
#include "PlatformAPI.h"
#include <eventqueue.h>
#include <stdint.h>
class EventProcessor : public Subscriber
{
    /*
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
public:
    EventProcessor();
    virtual ~EventProcessor();
    inline EventQueue<Event>& GetQueue() {return *m_Queue;}
    void OnEvent(Event e) override;
    void OnUpdate();
private:
    EventQueue<Event>* m_Queue;
    PlatformAPI* m_PlatformAPI;
    //used to map firmware keyCodes to XInput enums for keys

};
#endif
