#include "player-controller.hpp"
#include "ai-controller.hpp"
#include "board.hpp"
#include "../common/window.hpp"
using namespace tgame;

PlayerController::PlayerController(std::shared_ptr<Board> board, PawnTeam team, const Window &wnd) :
    Controller(board, team), skipController_(std::make_shared<AIController>(board, team))
{
    cellSize_ = wnd.getViewportSquareSize() / board->getDim();
    skipController_->setOnPlaceCallback([this]()
    {
        onPlaced();
    });
}

void PlayerController::allowMove()
{
    Controller::allowMove();
    skipController_->allowMove();
}

void PlayerController::setTarget(Position pos)
{
    Controller::setTarget(pos);
    skipController_->setTarget(pos);
}

void PlayerController::onMouseClick(uint32_t x, uint32_t y)
{
    auto cellPos = getCellByMousePosition(x, y);
    if (takenPawn_)
        place(cellPos);
    else
        take(cellPos);
}

void PlayerController::onMouseMove(uint32_t x, uint32_t y)
{
    auto cellPos = getCellByMousePosition(x, y);
}

void PlayerController::onSkipPressed()
{
    drop();
    skipController_->allowMove();
    skipController_->doMove();
}

Position PlayerController::getCellByMousePosition(uint32_t x, uint32_t y)
{
    auto cellX = (x - (x % cellSize_)) / cellSize_;
    auto cellY = (y - (y % cellSize_)) / cellSize_;
    return {(int16_t) cellX, (int16_t) cellY};
}