#pragma once
#include "Event.h"
#include "Subscriber.h"
class Publisher
{
    public:
    void AddSubscriber(Subscriber& subscriber) {
        m_Subscribers[m_SubCount] = &subscriber;
        m_SubCount = (m_SubCount + 1) % 3;
    }

    void publish(Event e) {
        bool handled = false;
        for(int i = 0; i < m_SubCount; i ++) {
            handled = m_Subscribers[m_SubCount]->OnEvent(e);
            if (handled) break;
        }
    }
    private:
        Subscriber* m_Subscribers[3];
        int m_SubCount = 0;
};