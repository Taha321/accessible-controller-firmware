#include "MacroMiddleware.h"
#include "assert.h"

MacroMiddleware::MacroMiddleware() 
{
  m_EventQueue = new QueueArray<Event>();
  //TO DO: load macros from storage
};

MacroMiddleware::~MacroMiddleware()
{
  QueueArray<Event>& queue = *(m_EventQueue);
  while (!queue.isEmpty())
    queue.dequeue();
  delete m_EventQueue;
}


void MacroMiddleware::OnEvent(Event e) 
{
  switch(m_State)
  {
    case State::RECORDING:
      recordEvent(e);
      break;
      
    case State::IDLE:
      if(e.code == keycode::Macro1) 
      {
        executeMacro(1);
        break;
      }
      if(e.code == keycode::Record_Macro) 
      {
        startRecording();
        break;
      }
     default:
        publish(e);
  }  
}

void MacroMiddleware::recordEvent(Event e)
{
  if(e.code == keycode::Macro1) return;
  if(e.code == keycode::Record_Macro) 
    m_State = State::IDLE;
  else {
    m_EventQueue->enqueue(e);
  }
}

void MacroMiddleware::startRecording()
{
  QueueArray<Event>& queue = *(m_EventQueue);
  while(!queue.isEmpty())
    queue.dequeue();
  m_State = State::RECORDING;
}


void MacroMiddleware::executeMacro(int macro)
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
