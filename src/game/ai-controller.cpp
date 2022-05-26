#include "ai-controller.hpp"
#include "board.hpp"
#include <algorithm>
#include <cmath>
using namespace tgame;

AIController::AIController(std::shared_ptr<Board> board, PawnTeam team) :
    Controller(board, team)
{

}

void AIController::doMove()
{
    auto board = board_.lock();
    if (!board)
        return;
    auto teamPositions = board->getTeamPositions(controlledTeam_);
    // sort by distance: far -> nearest to target
    std::sort(teamPositions.begin(), teamPositions.end(), [this](Position &a, Position &b) -> bool
    {
        auto aDiff = targetPosition_ - a;
        auto bDiff = targetPosition_ - b;
        return std::sqrt(std::pow(aDiff.x, 2) + std::pow(aDiff.y, 2)) > std::sqrt(std::pow(bDiff.x, 2) + std::pow(bDiff.y, 2));
    });
    // приоритет:
    // подтянуть дальние от цели (кроме любового хода)
    // направить ближние к цели (кроме любового хода)
    for (auto &pos : teamPositions)
    {
        if (tryMove(pos, false))
            return;
    }
    // любой ход дальних
    for (auto &pos : teamPositions)
    {
        if (tryMove(pos, true))
            return;
    }
}

bool AIController::tryMove(Position pos, bool anyMove)
{
    if (!take(pos))
        return false;
    auto direction = targetPosition_ - pos;
    if (direction.x != 0)
        direction.x /= std::abs(direction.x);
    if (direction.y != 0)
        direction.y /= std::abs(direction.y);
    if (direction.x && place({(int16_t) (pos.x + direction.x), pos.y}))
        return true;
    if (direction.y && place({pos.x, (int16_t) (pos.y + direction.y)}))
        return true;
    if (anyMove && direction.x && place({(int16_t) (pos.x - direction.x), pos.y}))
        return true;
    if (anyMove && direction.y && place({pos.x, (int16_t) (pos.y - direction.y)}))
        return true;
    drop();
    return false;
}
