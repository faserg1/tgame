#pragma once

#include <SDL2/SDL.h>
#include "../game/board.hpp"

namespace tgame
{
    class RenderBoard
    {
    public:
        RenderBoard(SDL_Renderer *renderer, uint16_t cellSize);
        void draw(const Board &board);
    private:
        SDL_Renderer *const renderer_;
        const uint16_t cellSize_;
    };
}