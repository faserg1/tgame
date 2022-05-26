#pragma once

#include <memory>
#include "../common/window.hpp"

namespace tgame
{
    class RenderImpl;
    class RenderBoard;
    class RenderPawn;

    class Board;

    class Render
    {
    public:
        Render(std::shared_ptr<Window> wnd, const Board &board);
        ~Render();

        void draw(const Board &board);
        void present();
    private:
        std::unique_ptr<RenderImpl> impl_;
        const std::shared_ptr<Window> wnd_;
        std::shared_ptr<RenderBoard> renderBoard_;
        std::shared_ptr<RenderPawn> renderPawn_;
    };
}