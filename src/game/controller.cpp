#include "controller.hpp"
#include "board.hpp"
using namespace tgame;

Controller::Controller(std::shared_ptr<Board> board, PawnTeam team) :
    board_(board), controlledTeam_(team)
{

}

void Controller::allowMove()
{
    moveAllowed_ = true;
}

void Controller::setOnPlaceCallback(std::function<void()> callback)
{
    placeCallback_ = callback;
}

bool Controller::take(Position pos)
{
    auto board = board_.lock();
    if (!board || takenPawn_ || !moveAllowed_)
        return false;
    if (auto pawn = board->getPawn(pos); pawn && pawn->getTeam() != controlledTeam_)
        return false;
    takenPawn_ = board->take(pos);
    prevPosition_ = pos;
    return true;
}

bool Controller::place(Position pos)
{
    auto board = board_.lock();
    if (pos == prevPosition_)
    {
        drop();
        return true;
    }
    if (!canMoveHere(pos))
        return false;
    auto placed = board->place(takenPawn_, pos);
    if (placed)
    {
        takenPawn_.reset();
        moveAllowed_ = false;
        onPlaced();
    }
    return placed;
}

void Controller::drop()
{
    auto board = board_.lock();
    if (!takenPawn_)
        return;
    board->place(takenPawn_, prevPosition_);
    takenPawn_.reset();
}

bool Controller::canMoveHere(Position pos)
{
    if (auto board = board_.lock(); !board || pos.x >= board->getDim() || pos.y >= board->getDim())
        return false;
    auto xDiff = std::abs(prevPosition_.x - pos.x);
    auto yDiff = std::abs(prevPosition_.y - pos.y);
    if (xDiff > 1 || yDiff > 1)
        return false;
    return (xDiff || yDiff) && !(xDiff && yDiff);
}

void Controller::onPlaced()
{
    if (placeCallback_)
            placeCallback_();
}

void Controller::setTarget(Position pos)
{
    targetPosition_ = pos;
}