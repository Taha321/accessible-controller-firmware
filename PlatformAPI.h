#pragma once
#include <stdint.h>
#include "InputHandler.h"

enum class PlatformAPIType
{
    None,
    XInput,
    Switch,
    Dualshock
};

class PlatformAPI {
    public:
        virtual void Press(uint8_t code) = 0;
        virtual void Release(uint8_t code) = 0;
        virtual void SetJoyStick(JoyStickType type, int16_t x, int16_t y) = 0 ;
    public:
        static PlatformAPIType Current() {return s_CurrentAPI;}
        static inline void SetAPI(PlatformAPIType api) {s_CurrentAPI = api;}
    private:
       static PlatformAPIType s_CurrentAPI;
};