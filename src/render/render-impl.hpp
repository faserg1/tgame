#pragma once

#include <SDL2/SDL.h>

namespace tgame
{
    struct RenderImpl
    {
        SDL_Renderer *renderer;
    };
}