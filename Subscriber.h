#pragma once
#include "Event.h"

class Subscriber
{
    public:
        virtual bool OnEvent(Event e) = 0;
};