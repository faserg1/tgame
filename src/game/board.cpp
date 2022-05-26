#include "board.hpp"
using namespace tgame;

Board::Board(uint16_t dim) :
    dim_(dim)
{
    cells_.resize(dim * dim);
}

size_t Board::cellIdx(Position pos) const
{
    return pos.y * dim_ + pos.x;
}

std::shared_ptr<Pawn> Board::take(Position pos)
{
    const auto idx = cellIdx(pos);
    auto item = cells_[idx];
    cells_[idx] = nullptr;
    return item;
}

bool Board::place(std::shared_ptr<Pawn> pawn, Position pos)
{
    const auto idx = cellIdx(pos);
    if (cells_[idx])
        return false;
    cells_[idx] = pawn;
    return true;
}

bool Board::has(Position pos)
{
    const auto idx = cellIdx(pos);
    return (bool) cells_[idx];
}


uint16_t Board::getDim() const
{
    return dim_;
}

std::shared_ptr<const Pawn> Board::getPawn(Position pos) const
{
    const auto idx = cellIdx(pos);
    if (!cells_[idx])
        return nullptr;
    return cells_[idx];
}

const std::vector<std::shared_ptr<Pawn>> &Board::getCells() const
{
    return cells_;
}

std::vector<Position> Board::getTeamPositions(PawnTeam team) const
{
    std::vector<Position> positions;
    positions.reserve(9);
    for (int16_t row = 0; row < dim_; row++)
    {
        for (int16_t col = 0; col < dim_; col++)
        {
            Position pos = {col, row};
            if (auto pawn = getPawn(pos); pawn && pawn->getTeam() == team)
                positions.push_back(pos);
        }
    }
    return std::move(positions);
}