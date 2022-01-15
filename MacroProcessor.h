#ifndef _MACROPROCESSOR_H
#define _MACROPROCESSOR_H

#include "EventProcessor.h"
#include "QueueArray.h"
#include "Event.h"
#include "KeyCode.h"

class MacroProcessor 
{
  public:
    MacroProcessor();
    virtual ~MacroProcessor();
    static void reset();    
    static bool OnEvent(Event e);
    void executeMacro(int macro);
    void toggleRecording();

  private:  
    QueueArray<Event>* m_EventQueue;
    bool m_IsRecording = false;
    bool m_IsExecuting = false;
  private:
    static MacroProcessor* s_Instance;
};

#endif
