#include "idle_state.h"

#include "fighter.h"

void IdleState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::IDLE);
}

void IdleState::tick(Fighter& fighter)
{
}

void IdleState::exit(Fighter& fighter)
{
}
