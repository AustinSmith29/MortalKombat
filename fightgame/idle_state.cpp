#include "idle_state.h"
#include "fighter.h"

IdleState::IdleState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::STAND)
{
}

void IdleState::enter(void *data)
{
	fighter.set_graphics(FighterGraphics::IDLE);
}

void IdleState::tick()
{
	fighter.get_animation()->loop();
}

void IdleState::exit()
{
}
