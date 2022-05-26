#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "pawn.hpp"

namespace tgame
{
    class Board
    {
    public:
        Board(uint16_t dim);

        std::shared_ptr<Pawn> take(Position pos);
        bool place(std::shared_ptr<Pawn> pawn, Position pos);
        bool has(Position pos);

        uint16_t getDim() const;
        std::shared_ptr<const Pawn> getPawn(Position pos) const;
        const std::vector<std::shared_ptr<Pawn>> &getCells() const;
        std::vector<Position> getTeamPositions(PawnTeam team) const;
    private:
        size_t cellIdx(Position pos) const;
    private:
        const uint16_t dim_;

        std::vector<std::shared_ptr<Pawn>> cells_;
    };
}