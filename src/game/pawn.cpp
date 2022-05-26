#include "pawn.hpp"
using namespace tgame;

Pawn::Pawn(PawnTeam team) :
    team_(team)
{

}

PawnTeam Pawn::getTeam() const
{
    return team_;
}