#ifndef _MACROPROCESSOR_H
#define _MACROPROCESSOR_H

#include "Event.h"
#include "KeyCode.h"
#include "Queue.h"
#include "EventProcessor.h"





class MacroProcessor : public EventProcessor
{
  private:  
    enum State
    {
      IDLE = 0,
      RECORDING,
    };

  public:
    MacroProcessor();
    virtual ~MacroProcessor();  
    void DispatchEvent(Event& e) override;

  private:
    void executeMacro(uint8_t macro);
    void recordEvent(Event& e);
    void startRecording();
    void readMacro(uint8_t macroNumber);
    void writeMacro(uint8_t macroNumber);
        
  private:
    static constexpr uint8_t MAX_SIZE = 128;
    Queue<Event>* m_EventQueue;
    State m_State = IDLE;
    unsigned long int m_LastEventTime; 
};


#endif
