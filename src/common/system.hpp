#pragma once

#include "input.hpp"
#include <memory>
#include <vector>

namespace tgame
{
    class System
    {
    public:
        bool init();
        void handleEvents();
        bool isQuitRequested() const;

        void subscribeToInput(std::shared_ptr<InputSubscriber> input);
    private:
        bool quitRequested_ = false;
        std::vector<std::weak_ptr<InputSubscriber>> inputSubs_;
    };
}