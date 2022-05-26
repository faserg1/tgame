#pragma once

#include "controller.hpp"

namespace tgame
{
    class AIController : public Controller
    {
    public:
        AIController(std::shared_ptr<Board> board, PawnTeam team);

        void doMove();
        
    private:
        bool tryMove(Position pos, bool anyMove);
    };
}