#include "idle_state.h"
#include "fighter.h"

void IdleState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
{
	fighter.set_graphics(FighterGraphics::IDLE);
	set_move_hook(FighterState::FightMoveHook::STAND);
}

void IdleState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.get_animation()->loop();
}

void IdleState::exit(Fighter& fighter, FighterStateMachine &machine)
{
}
