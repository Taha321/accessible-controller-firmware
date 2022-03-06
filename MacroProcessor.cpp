#include "QueueArray.h"
#include "MacroProcessor.h"
#include "InputHandler.h"
#include "EEPROM.h"
#define MACRO_MAX_SIZE 128*6 + 1
// Technically this may wear out the EEPROM but we need to define where they start and end.
#define LARGEST_EEPROM_ADDRESS 2047

MacroProcessor::MacroProcessor() 
{
  Serial.begin(9600); // For debugging
  m_EventQueue = new QueueArray<Event>();
  //TO DO: load macros from storage
  readMacro(1);

}

MacroProcessor::~MacroProcessor()
{
  
  writeMacro(1);
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
       Serial.print("Number of events on eventqueue...");
       Serial.println(m_EventQueue->count());
       Serial.print("Handled event = ");
       Serial.println(e.code);
    }  
  } 
}


void MacroProcessor::writeMacro(uint8_t macroNumber) {
    /* 
    We need to write byte by byte to EEPROM
    Also, we should store the last-written address so that we know where to write to next.
    */
    Event currentEvent;
    uint16_t address; 
    uint8_t eventSize = sizeof(Event);
    address = MACRO_MAX_SIZE*(macroNumber-1);
    Serial.println("Beginning write, initial address is:" + address);
    uint8_t queueSize = m_EventQueue->count(); // We need to store this so we know how long each macro is.
    EEPROM.update(address++, queueSize);
    for (uint8_t i = 0; i < queueSize; i++) {  
        Serial.println(address);
        if (address >= LARGEST_EEPROM_ADDRESS) {
            Serial.println("Tried to write to the largest possible address in EEPROM, and exiting loop...\n");
            break;
        }
        currentEvent = m_EventQueue->dequeue();
        EEPROM.put(address, currentEvent);
        m_EventQueue->enqueue(currentEvent);
        address += eventSize;
    }


}


void MacroProcessor::readMacro(uint8_t macroNumber) {
    uint16_t address = MACRO_MAX_SIZE*(macroNumber-1);
    uint8_t queueSize = EEPROM.read(address++);
    uint8_t eventSize = sizeof(Event);
    Serial.println("Beginning read...");
    for (uint8_t i = 0; i < queueSize; i++) {
        Event e;
        EEPROM.get(address, e);
        
        if (e.code < 0 || e.code > 20) {
          // The above condition could be subject to change as we add more buttons
          while (!m_EventQueue->isEmpty())
            m_EventQueue->dequeue();
          Serial.println("Event corrupted, emptied queue and exiting...");
          break;
        }
        Serial.print("Current address: ");
        Serial.println(address);
        Serial.println(e.code);
        m_EventQueue->enqueue(e);
        address += eventSize;
    }


}


void MacroProcessor::recordEvent(Event& e)
{

  if(e.code == keycode::Macro1) return;
  if(e.code == keycode::Record_Macro || m_EventQueue->count() == MAX_SIZE)
  { 
    m_State = State::IDLE;
    Serial.println("RECORDING STOPPED");  // For debugging
    writeMacro(1);

  }
  else {
    unsigned long currentEventTime = millis();
    e.wait = currentEventTime - m_LastEventTime;
    m_LastEventTime = currentEventTime; // Set to the clocked currentEventTime


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
  Serial.print("Size of event queue in execution fxn ");
  Serial.println(size);
  
  for(uint8_t i = 0; i < size; i++) 
  {
    Event e = m_EventQueue->dequeue();
    InputHandler::GetEventQueue().enqueue(e);
    m_EventQueue->enqueue(e);

  }
}
