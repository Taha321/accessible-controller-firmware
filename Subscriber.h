#pragma once
#include "Event.h"

class Subscriber
{
    public:
        virtual void OnEvent(Event e) = 0;
};