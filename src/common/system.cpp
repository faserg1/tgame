#include "system.hpp"
#include <SDL2/SDL.h>
using namespace tgame;

bool System::init()
{
    auto result = SDL_Init(0);
    if (result)
        return false;
    return true;
}

void System::handleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EventType::SDL_QUIT:
                quitRequested_ = true;
                break;
            case SDL_EventType::SDL_MOUSEBUTTONDOWN:
            {
                auto mouseEvent = event.button;
                if (mouseEvent.button == SDL_BUTTON_LEFT)
                {
                    for (auto &weakInput : inputSubs_)
                    {
                        if (auto input = weakInput.lock())
                            input->onMouseClick(mouseEvent.x, mouseEvent.y);
                    }
                }
                break;
            }
            case SDL_EventType::SDL_MOUSEMOTION:
            {
                auto mouseEvent = event.motion;
                for (auto &weakInput : inputSubs_)
                {
                    if (auto input = weakInput.lock())
                        input->onMouseMove(mouseEvent.x, mouseEvent.y);
                }
                break;
            }
            case SDL_EventType::SDL_KEYDOWN:
            {
                auto keyEvent = event.key;
                if (keyEvent.keysym.sym == SDLK_LCTRL)
                {
                    for (auto &weakInput : inputSubs_)
                    {
                        if (auto input = weakInput.lock())
                            input->onSkipPressed();
                    }
                }
            }
        }
    }
}

bool System::isQuitRequested() const
{
    return quitRequested_;
}

void System::subscribeToInput(std::shared_ptr<InputSubscriber> input)
{
    inputSubs_.push_back(input);
}