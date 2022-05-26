#pragma once

#include <cstdint>

namespace tgame
{
    class InputSubscriber
    {
    public:
        virtual void onMouseClick(uint32_t x, uint32_t y) = 0;
        virtual void onMouseMove(uint32_t x, uint32_t y) = 0;
        virtual void onSkipPressed() = 0;
    };
}