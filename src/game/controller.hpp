#pragma once

#include <memory>
#include <functional>
#include "pawn.hpp"

namespace tgame
{
    class Board;

    class Controller
    {
    public:
        virtual void allowMove();
        virtual void setTarget(Position pos);
        void setOnPlaceCallback(std::function<void()> callback);
    protected:
        Controller(std::shared_ptr<Board> board, PawnTeam team);

        bool take(Position pos);
        bool place(Position pos);
        void drop();

        bool canMoveHere(Position pos);
        void onPlaced();
    protected:
        const std::weak_ptr<Board> board_;
        const PawnTeam controlledTeam_;
        std::shared_ptr<Pawn> takenPawn_;
        Position prevPosition_;

        bool moveAllowed_;
        Position targetPosition_;
    private:
        std::function<void()> placeCallback_;
    };
}