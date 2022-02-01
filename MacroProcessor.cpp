#include "QueueArray.h"
#include "MacroProcessor.h"
#include "InputHandler.h"

MacroProcessor::MacroProcessor() 
{
  m_EventQueue = new QueueArray<Event>();
  //TO DO: load macros from storage
}

MacroProcessor::~MacroProcessor()
{
  while (!m_EventQueue->isEmpty())
    m_EventQueue->dequeue();

  delete[] m_EventQueue;  
}


void MacroProcessor::DispatchEvent(Event& e) 
{
  if(e.Handled == false)
  {
    switch(m_State)
    {
      case State::RECORDING:
        recordEvent(e);
        e.Handled = true;
        break;
        
      case State::IDLE:
        e.Handled = true;
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
        else
        {
          e.Handled = false;
          break;
        }
    }
    if(e.Handled == true)   //For debugging
    {
       Serial.print("sizeof(m_EventQueue)=");
       Serial.println(sizeof(m_EventQueue));
       Serial.print("Current Macro's Queue Size = ");
       Serial.println(m_EventQueue->count());
       Serial.print("Handled event = ");
       Serial.println(e.code);
    }  
  } 
}

void MacroProcessor::recordEvent(Event& e)
{

  if(e.code == keycode::Macro1) return;
  if(e.code == keycode::Record_Macro || m_EventQueue->count() == MAX_SIZE)
  { 
    m_State = State::IDLE;
    Serial.println("RECORDING STOPPED");  // For debugging
  }
  else {
    unsigned long currentEventTime = millis();
    e.wait = currentEventTime - m_LastEventTime;
    m_LastEventTime = currentEventTime; // Set to the clocked currentEventTime
    Serial.print("Enqueuing event = ");
    Serial.println(e.code);

    m_EventQueue->enqueue(e);
  }
}

void MacroProcessor::startRecording()
{
  while(!m_EventQueue->isEmpty())
    m_EventQueue->dequeue();
  m_LastEventTime = millis();
  m_State = State::RECORDING;
  Serial.println("RECORDING STARTED");  // For debugging
}


void MacroProcessor::executeMacro(uint8_t macro)
{
  uint8_t size = m_EventQueue->count();   
  for(uint8_t i = 0; i < size; i++) 
  {
    
    Event e = m_EventQueue->dequeue();
    InputHandler::GetEventQueue().enqueue(e);
    m_EventQueue->enqueue(e);

  }
}
