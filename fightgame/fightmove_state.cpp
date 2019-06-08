#include "fightmove_state.h"
#include "fighter.h"

void FightMoveState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::FIGHT_MOVE);
}

void FightMoveState::tick(Fighter& fighter)
{
}

void FightMoveState::exit(Fighter& fighter)
{
}