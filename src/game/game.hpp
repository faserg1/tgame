#pragma once

#include <memory>
#include "board.hpp"

namespace tgame
{
    class Window;
    class InputSubscriber;

    class AIController;
    class PlayerController;

    class GameStateMachine;

    class Game
    {
    public:
        Game(const Window &wnd);

        void prepare();
        const Board &getBoard() const;

        bool isTeamWin(PawnTeam team) const;
        void switchLeadingTeam(PawnTeam team);
        void doMoveByAI();

        std::shared_ptr<InputSubscriber> getInputSubscriber() const;
    private:
        std::shared_ptr<Board> board_;
        std::shared_ptr<AIController> aiController_;
        std::shared_ptr<PlayerController> playerController_;

        std::shared_ptr<GameStateMachine> stateMachine_;
    };
}