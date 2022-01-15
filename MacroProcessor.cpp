#include "MacroProcessor.h"
#include "assert.h"
MacroProcessor* MacroProcessor::s_Instance = nullptr;

MacroProcessor::MacroProcessor() 
{
  assert(!s_Instance);
  s_Instance = this;
  m_EventQueue = new QueueArray<Event>();
  //TO DO: load macros from storage
};

MacroProcessor::~MacroProcessor()
{
  QueueArray<Event>& queue = *(s_Instance->m_EventQueue);
  while (!queue.isEmpty())
    queue.dequeue();
  delete s_Instance->m_EventQueue;
}


bool MacroProcessor::OnEvent(Event e) 
{
  switch(s_Instance->m_State)
  {
    case State::RECORDING:
      s_Instance->recordEvent(e);
      return true;
      
    case State::EXECUTING:
      return false;
      
    case State::IDLE:
      if(e.code == keycode::Macro1) 
      {
        s_Instance->executeMacro(1);
        return true;
      }
      if(e.code == keycode::Record_Macro);
        s_Instance->startRecording();
        return true;
     default:
       return false;
  }  
}

void MacroProcessor::recordEvent(Event e)
{
  if(e.code == keycode::Macro1) return;
  if(e.code == keycode::Record_Macro) 
    s_Instance->m_State = State::IDLE;
  else {
    s_Instance->m_EventQueue->enqueue(e);
  }
}

void MacroProcessor::startRecording()
{
  QueueArray<Event>& queue = *(s_Instance->m_EventQueue);
  while(!queue.isEmpty())
    queue.dequeue();
  s_Instance->m_State = State::RECORDING;
}


void MacroProcessor::executeMacro(int macro)
{
  QueueArray<Event>& queue = *(s_Instance->m_EventQueue);
  // Takes macro number (i.e 1, 2, ...)
  int size = queue.count();   
  for(int i = 0; i < size; i++) 
  {
    Event e = queue.dequeue();
    EventProcessor::Get().GetQueue().putQ(e);
    queue.enqueue(e);
  }
  s_Instance->m_State = State::IDLE;
}
