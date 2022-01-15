#ifndef _MACROPROCESSOR_H
#define _MACROPROCESSOR_H

#include "InputHandler.h"
#include <QueueArray.h>

class MacroProcessor 
{
  public:
    MacroProcessor() = delete;
    MacroProcessor(const MacroProcessor&) = delete;
    MacroProcessor& operator= (const MacroProcessor&) = delete;
    ~MacroProcessor() = delete;

    static void Begin();
    static void reset();    
    static bool OnEvent(Event e);

  private:
    static EventQueue<Event>* EQ;                                         //Pointer to the targetted event queue   
    static QueueArray<Event> s_eventQueue;
    static s_isRecording = false;\
    static s_isExecuting = false;
};

extern MacroProcessor MP;
#endif


