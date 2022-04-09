#ifndef _EVENTPROCESSOR_H
#define _EVENTPROCESSOR_H
#include "Event.h"

class EventProcessor
{
 public:
    virtual void DispatchEvent(Event& e) = 0;
};


#endif
