#pragma once

#include "controller.hpp"
#include "../common/input.hpp"

namespace tgame
{
    class Window;

    class AIController;

    class PlayerController : public Controller, public virtual InputSubscriber
    {
    public:
        PlayerController(std::shared_ptr<Board> board, PawnTeam team, const Window &wnd);

        void allowMove() override;
        void setTarget(Position pos) override;

        void onMouseClick(uint32_t x, uint32_t y) override;
        void onMouseMove(uint32_t x, uint32_t y) override;
        void onSkipPressed() override;
    private:
        Position getCellByMousePosition(uint32_t x, uint32_t y);
    private:
        int cellSize_;

        std::shared_ptr<AIController> skipController_;
    };
}