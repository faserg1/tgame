#include "render-pawn.hpp"
#include <SDL_image.h>
using namespace tgame;

RenderPawn::RenderPawn(SDL_Renderer *renderer, uint16_t cellSize) :
    renderer_(renderer), cellSize_(cellSize)
{
    blackPawn_ = IMG_LoadTexture(renderer, "./resources/black-pawn.png");
    whitePawn_ = IMG_LoadTexture(renderer, "./resources/white-pawn.png");
}

void RenderPawn::draw(const Pawn &pawn, const Position &pos)
{
    SDL_Rect drawRect
    {
        pos.x * cellSize_,
        pos.y * cellSize_,
        cellSize_,
        cellSize_
    };
    if (auto texture = getTextureFor(pawn))
        SDL_RenderCopy(renderer_, texture, NULL, &drawRect);
}

SDL_Texture *RenderPawn::getTextureFor(const Pawn &pawn)
{
    switch (pawn.getTeam())
    {
    case PawnTeam::White:
        return whitePawn_;
    case PawnTeam::Black:
        return blackPawn_;
    default:
        return nullptr;
    }
}