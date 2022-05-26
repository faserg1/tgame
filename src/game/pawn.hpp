#pragma once

#include "position.hpp"

namespace tgame
{
    enum class PawnTeam
    {
        White,
        Black
    };
    
    class Pawn
    {
    public:
        Pawn(PawnTeam team);

        PawnTeam getTeam() const;
    private:
        const PawnTeam team_;
    };
}