#include "EventProcessor.h"
#include "InputHandler.h"
#include "XInputAPI.h"
#include "assert.h"

static PlatformAPI* InitPlatformAPI()
{
  switch(PlatformAPI::Current())
  {
      case PlatformAPIType::XInput: return new XInputAPI(); 
      case PlatformAPIType::None:
        PlatformAPI::SetAPI(PlatformAPIType::XInput);
        return new XInputAPI();
      default:
        assert(false);
  }
}

EventProcessor::EventProcessor()
{
  m_Queue = new EventQueue<Event>();
  m_PlatformAPI = InitPlatformAPI();
}

EventProcessor::~EventProcessor() {

}

void EventProcessor::OnEvent(Event e) {
    m_Queue->putQ(e);
}

void EventProcessor::OnUpdate() 
{
    Event e;
    if (m_Queue->getQ(e)) // Will return true if there is an event on the queue, false if it's empty
    {
        if(e.eventType == Event::Press)
            m_PlatformAPI->Press(e.code);

        else if(e.eventType == Event::Release)
            m_PlatformAPI->Release(e.code); 
        
    }
    m_PlatformAPI->SetJoyStick(JoyStickType::Right, InputHandler::GetRightAnalog().x, InputHandler::GetRightAnalog().y);
    m_PlatformAPI->SetJoyStick(JoyStickType::Left, InputHandler::GetLeftAnalog().x, InputHandler::GetLeftAnalog().y);
}
