#include "MacroProcessor.h"
#include "assert.h"

MacroProcessor::MacroProcessor() 
{
  m_EventQueue = new QueueArray<Event>();
  //TO DO: load macros from storage
};

MacroProcessor::~MacroProcessor()
{
  QueueArray<Event>& queue = *(m_EventQueue);
  while (!queue.isEmpty())
    queue.dequeue();
  delete m_EventQueue;
}


bool MacroProcessor::OnEvent(Event e) 
{
  switch(m_State)
  {
    case State::RECORDING:
      recordEvent(e);
      return true;
      
    case State::IDLE:
      if(e.code == keycode::Macro1) 
      {
        executeMacro(1);
        return true;
      }
      if(e.code == keycode::Record_Macro);
        startRecording();
        return true;
     default:
       return false;
  }  
}

void MacroProcessor::recordEvent(Event e)
{
  if(e.code == keycode::Macro1) return;
  if(e.code == keycode::Record_Macro) 
    m_State = State::IDLE;
  else {
    m_EventQueue->enqueue(e);
  }
}

void MacroProcessor::startRecording()
{
  QueueArray<Event>& queue = *(m_EventQueue);
  while(!queue.isEmpty())
    queue.dequeue();
  m_State = State::RECORDING;
}


void MacroProcessor::executeMacro(int macro)
{
  QueueArray<Event>& queue = *(m_EventQueue);
  int size = queue.count();   
  for(int i = 0; i < size; i++) 
  {
    Event e = queue.dequeue();
    publish(e);
    queue.enqueue(e);
  }
}
