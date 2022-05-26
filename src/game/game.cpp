#include "game.hpp"
#include "game-sm.hpp"
#include "ai-controller.hpp"
#include "player-controller.hpp"
using namespace tgame;

Game::Game(const Window &wnd) :
    board_(std::make_unique<Board>(8)),
    aiController_(std::make_shared<AIController>(board_, PawnTeam::Black)),
    playerController_(std::make_shared<PlayerController>(board_, PawnTeam::White, wnd)),
    stateMachine_(std::make_shared<GameStateMachine>(this))
{
    auto placeCallback = [this]()
    {
        stateMachine_->machine.process_event(MoveDone{});
    };

    aiController_->setOnPlaceCallback(placeCallback);
    playerController_->setOnPlaceCallback(placeCallback);

    aiController_->setTarget({8, 8});
    playerController_->setTarget({0, 0});
}

void Game::prepare()
{
    for (int16_t row = 0; row < 3; row++)
    {
        for (int16_t col = 0; col < 3; col++)
        {
            board_->place(std::make_shared<Pawn>(PawnTeam::Black), {col, row});
            Position backwardsPos {(int16_t) (board_->getDim() - col - 1), (int16_t) (board_->getDim() - row - 1)};
            board_->place(std::make_shared<Pawn>(PawnTeam::White), backwardsPos);
        }
    }
}

const Board &Game::getBoard() const
{
    return *board_;
}

bool Game::isTeamWin(PawnTeam team) const
{
    for (int16_t row = 0; row < 3; row++)
    {
        for (int16_t col = 0; col < 3; col++)
        {
            Position pos {col, row};
            Position backwardsPos {(int16_t) (board_->getDim() - row - 1), (int16_t) (board_->getDim() - col - 1)};
            auto pawn = board_->getPawn(team == PawnTeam::White ? pos : backwardsPos);
            if (!pawn || pawn->getTeam() != team)
                return false;
        }
    }
    return true;
}

void Game::switchLeadingTeam(PawnTeam team)
{
    if (team == PawnTeam::Black)
        aiController_->allowMove();
    else if (team == PawnTeam::White)
        playerController_->allowMove();
}

void Game::doMoveByAI()
{
    aiController_->doMove();
}

std::shared_ptr<InputSubscriber> Game::getInputSubscriber() const
{
    return std::static_pointer_cast<InputSubscriber>(playerController_);
}