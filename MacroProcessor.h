#ifndef _MACROPROCESSOR_H
#define _MACROPROCESSOR_H
#include "Event.h"
#include "KeyCode.h"


class MacroProcessor
{
  
  public:
    MacroProcessor();
    virtual ~MacroProcessor();  
    void DispatchEvent(Event& e);

  private:
    void executeMacro(uint8_t macro);
    void recordEvent(Event& e);
    void startRecording();
    static constexpr uint8_t MAX_SIZE = 128;
    enum State
    {
      IDLE = 0,
      RECORDING,
    };  
    QueueArray<Event>* m_EventQueue;
    State m_State = IDLE;
    unsigned long m_LastEventTime; 
};

#endif
