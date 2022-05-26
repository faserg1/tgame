#include "render-board.hpp"
using namespace tgame;

RenderBoard::RenderBoard(SDL_Renderer *renderer, uint16_t cellSize) :
    renderer_(renderer), cellSize_(cellSize)
{
    
}

void RenderBoard::draw(const Board &board)
{
    uint16_t colorShift = 0;
    for (uint16_t row = 0; row < board.getDim(); row++, colorShift++)
    {
        for (uint16_t col = 0; col < board.getDim(); col++, colorShift++)
        {
            if (colorShift % 2)
                SDL_SetRenderDrawColor(renderer_, 170, 170, 170, 255);
            else
                SDL_SetRenderDrawColor(renderer_, 60, 60, 60, 255);
            SDL_Rect rect
            {
                col * cellSize_,
                row * cellSize_,
                cellSize_,
                cellSize_
            };
            SDL_RenderFillRect(renderer_, &rect);
        }
    }
    
}