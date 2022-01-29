#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H

#include "QueueArray.h"
#include "MacroProcessor.h"
#include "PlatformAPI.h"


class EventProcessor
{
    /*
    Take events off the queue and process them, transforming them into
    Xinput presses.
    */
public:
    EventProcessor();
    virtual ~EventProcessor();
    
    void OnUpdate();
    
private:
    MacroProcessor m_MacroProcessor;
    PlatformAPI* m_PlatformAPI;
    //used to map firmware keyCodes to XInput enums for keys
};
#endif
