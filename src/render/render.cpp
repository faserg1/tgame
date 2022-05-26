#include "render.hpp"
#include "render-impl.hpp"
#include "render-board.hpp"
#include "render-pawn.hpp"
#include "../common/window.hpp"
#include "../common/window-impl.hpp"
#include <SDL2/SDL.h>
using namespace tgame;

Render::Render(std::shared_ptr<Window> wnd, const Board &board) :
    impl_(std::make_unique<RenderImpl>()), wnd_(wnd)
{
    impl_->renderer = SDL_CreateRenderer(wnd->getImpl().wnd, -1, SDL_RENDERER_ACCELERATED);

    auto cellSize = wnd->getViewportSquareSize() / board.getDim();
    renderBoard_ = std::make_shared<RenderBoard>(impl_->renderer, cellSize);
    renderPawn_ = std::make_shared<RenderPawn>(impl_->renderer, cellSize);
    SDL_SetRenderDrawColor(impl_->renderer, 128, 128, 128, 255);
}

Render::~Render()
{
    SDL_DestroyRenderer(impl_->renderer);
}

void Render::draw(const Board &board)
{
    SDL_RenderClear(impl_->renderer);
    renderBoard_->draw(board);
    
    for (int16_t row = 0; row < board.getDim(); row++)
    {
        for (int16_t col = 0; col < board.getDim(); col++)
        {
            auto pos = Position{col, row};
            if (auto pawn = board.getPawn(pos))
                renderPawn_->draw(*pawn, pos);
        }
    }
}

void Render::present()
{
    SDL_RenderPresent(impl_->renderer);
}