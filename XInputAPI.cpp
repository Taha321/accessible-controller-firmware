#include "XInputAPI.h"
#include "assert.h"

uint8_t XInputAPI::nativeToXInput(uint8_t code) 
{
    return keyCodeMap[code];
}

void XInputAPI::Press(uint8_t code) 
{
    uint8_t XInputKeyCode = nativeToXInput(code);
    XInput.press(XInputKeyCode);
}

void XInputAPI::Release(uint8_t code)
{
    uint8_t XInputKeyCode = nativeToXInput(code);
    XInput.release(XInputKeyCode);
}

void XInputAPI::SetJoyStick(JoyStickType type, int16_t x, int16_t y)
{
    switch(type){
        case JoyStickType::Left:
            XInput.setJoystick(JOY_LEFT,x,y);
            break;
        case JoyStickType::Right:
            XInput.setJoystick(JOY_RIGHT,x,y);
            break;
        case JoyStickType::None:
        default: 
            assert(false);   
    }
}

const uint8_t XInputAPI::keyCodeMap[] = { BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, DPAD_RIGHT, DPAD_LEFT, DPAD_UP, DPAD_DOWN,
                                                TRIGGER_LEFT, TRIGGER_RIGHT, JOY_LEFT, JOY_LEFT, JOY_RIGHT, JOY_RIGHT }; 
