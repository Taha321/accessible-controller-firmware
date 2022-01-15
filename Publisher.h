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
        for(int i = 0; i < m_SubCount; i ++) {
            m_Subscribers[m_SubCount]->OnEvent(e);
        }
    }
    private:
        Subscriber* m_Subscribers[3];
        int m_SubCount = 0;
};