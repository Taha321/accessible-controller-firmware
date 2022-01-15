#include "MacroProcessor.h"

void MacroProcessor::Begin(EventQueue<Event>& queue) 
{
  EQ = queue;
  s_eventQueue = new QueueArray<Event>();
  //load in data;
};

void MacroProcessor::reset()
{
  while (!s_eventQueue.isEmpty())
    s_Instance.eventQueue.dequeue();
}


bool MacroProcessor::OnEvent(Event e) 
{
  // Handle macro record button press
  if(e.keyCode == keycode::Record_Macro)
  {
    toggleRecording();
    return true;
  }

  // Handle macro execute press
  if(!s_isRecording)
  {
    if(e.keyCode == keycode::Macro1) 
    {
      executeMacro(1);
      return true;
    }  
  }
  
  // Handle Everything else
  if(s_isRecording) 
  {
    s_eventQueue.enqueue(e);
    return true;
  }

  return false;
}

void MacroProcessor::toggleRecording() 
{
  if(!s_isRecording) 
  {
    while(!s_eventQueue.isEmpty())
      s_eventQueue.dequeue();

    s_isRecording = true;
  }
  else 
    s_isRecording = false;
}

void MacroProcessor::executeMacro(int macro)
{
  // Takes macro number (i.e 1, 2, ...)
  int size = s_eventQueue.size();   
  for(int i = 0; i < size; i++) 
  {
    Event e = s_eventQueue.dequeue();
    EQ->enqueue(e);
    s_eventQueue.enqueue(e);
  }
}


