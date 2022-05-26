#pragma once

#include <memory>
#include <boost/sml.hpp>

namespace tgame
{
    class Game;

    /* States */ 
    auto sGameStart = boost::sml::state<struct GameStartState>;

    auto sPlayerMove = boost::sml::state<struct PlayerMoveState>;
    auto sComputerMove = boost::sml::state<struct ComputerMoveState>;

    auto sPlayerWin = boost::sml::state<struct PlayerWinState>;
    auto sPlayerLose = boost::sml::state<struct PlayerLoseState>;

    /* Events */

    struct MoveDone {};

    /* Guards */

    const auto playerWinGuard = [](Game *game) -> bool
    {
        return game->isTeamWin(PawnTeam::White);
    };

    const auto playerLoseGuard = [](Game *game) -> bool
    {
        return game->isTeamWin(PawnTeam::Black);
    };

    /* Actions */

    const auto doAIMove = [](Game *game)
    {
        game->doMoveByAI();
    };

    const auto switchToPlayer = [](Game *game)
    {
        game->switchLeadingTeam(PawnTeam::White);
    };

    const auto switchToComputer = [](Game *game)
    {
        game->switchLeadingTeam(PawnTeam::Black);
    };

    struct GameStateMachineTable
    {
        auto operator()() const noexcept
        {
            using namespace boost::sml;

            return make_transition_table
            (
                *sGameStart = sPlayerMove,
                sPlayerMove + event<MoveDone> [!playerWinGuard] = sComputerMove,
                sComputerMove + event<MoveDone> [!playerLoseGuard] = sPlayerMove,
                sComputerMove + on_entry<_> / (switchToComputer, doAIMove),
                sPlayerMove + on_entry<_> / (switchToPlayer),
                sPlayerMove + event<MoveDone> [playerWinGuard] = sPlayerWin,
                sComputerMove + event<MoveDone> [playerLoseGuard] = sPlayerLose,
                sPlayerLose = X,
                sPlayerWin = X
            );
        }
    };

    struct GameStateMachine
    {
        GameStateMachine(Game *game) :
            machine(game)
        {

        }
        boost::sml::sm<GameStateMachineTable> machine;
    };
}