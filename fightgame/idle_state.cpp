#include "idle_state.h"
#include "fighter.h"

void IdleState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::IDLE);
	set_move_hook(FighterState::FightMoveHook::STAND);
}

void IdleState::tick(Fighter& fighter)
{
	fighter.get_animation()->loop();
}

void IdleState::exit(Fighter& fighter)
{
}
