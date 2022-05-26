#pragma once

#include <SDL2/SDL.h>
#include "../game/pawn.hpp"

namespace tgame
{
    class RenderPawn
    {
    public:
        RenderPawn(SDL_Renderer *renderer, uint16_t cellSize);

        void draw(const Pawn &pawn, const Position &pos);

    private:
        SDL_Texture *getTextureFor(const Pawn &pawn);
    private:
        SDL_Renderer *const renderer_;
        const uint16_t cellSize_;
        SDL_Texture *whitePawn_;
        SDL_Texture *blackPawn_;
    };
}