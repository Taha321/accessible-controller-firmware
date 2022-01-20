#pragma once
#include "PlatformAPI.h"
#include "XInput.h"
#include "InputHandler.h"
#include <stdint.h>

class XInputAPI : public PlatformAPI
{
    public:
        void Press(uint8_t code) override;
        void Release(uint8_t code) override;
        void SetJoyStick(JoyStickType type, int16_t x, int16_t y) override;
        
    private:
        static uint8_t nativeToXInput(uint8_t code);
        static const uint8_t keyCodeMap[14];
};
