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
  bool isRecording = s_Instance->m_IsRecording;
  bool isExecuting = s_Instance->m_IsExecuting;
  
  // Handle macro record button press
  if(!isExecuting) {
    if(e.code == keycode::Record_Macro)
    {
      s_Instance->toggleRecording();
      return true;
    }
   return false;
  }

  // Handle macro execute press
  if(!isRecording && !isExecuting)
  {
    if(e.code == keycode::Macro1) 
    {
      s_Instance->executeMacro(1);
      return true;
    }  
  }
  
  // Handle Everything else
  if(isRecording && !isExecuting) 
  {
    s_Instance->m_EventQueue->enqueue(e);
    return true;
  }

  return false;
}

void MacroProcessor::toggleRecording() 
{
  bool isRecording = s_Instance->m_IsRecording;
  QueueArray<Event>& queue = *(s_Instance->m_EventQueue);
  if(!isRecording) 
  {
    while(!queue.isEmpty())
      queue.dequeue();

    s_Instance->m_IsRecording = true;
  }
  else 
    s_Instance->m_IsRecording = false;
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
}
