#ifndef _MACROMIDDLEWARE_H
#define _MACROMIDDLEWARE_H

#include "EventProcessor.h"
#include "QueueArray.h"
#include "Event.h"
#include "KeyCode.h"
#include "Publisher.h"
#include "Subscriber.h"
class MacroMiddleware : public Subscriber, public Publisher
{
  
  public:
    MacroMiddleware();
    virtual ~MacroMiddleware();  
    void OnEvent(Event e) override;

  private:
    void executeMacro(int macro);
    void recordEvent(Event e);
    void startRecording();
    
    enum State
    {
      IDLE = 0,
      RECORDING,
    };  
    QueueArray<Event>* m_EventQueue;
    bool m_IsRecording = false;
    bool m_IsExecuting = false;
    State m_State = IDLE;
};

#endif
