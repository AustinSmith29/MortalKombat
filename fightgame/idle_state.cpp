#include "idle_state.h"

#include "fighter.h"

void IdleState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::IDLE);
	set_move_hook(FighterState::FightMoveHook::STAND);
}

void IdleState::tick(Fighter& fighter)
{
}

void IdleState::exit(Fighter& fighter)
{
}
