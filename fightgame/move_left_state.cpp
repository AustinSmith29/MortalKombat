#include "move_left_state.h"
#include "fighter.h"

MoveLeftState::MoveLeftState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::STAND)
{
}

void MoveLeftState::enter(void *data)
{
	if (fighter.get_orientation() == Orientation::LEFT)
	{
		fighter.set_graphics(FighterGraphics::WALK_FORWARD);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::WALK_BACKWARD);
	}
	fighter.set_velocity_x(-1);
}

void MoveLeftState::tick()
{
	fighter.get_animation()->loop();
}

void MoveLeftState::exit()
{
	fighter.set_velocity_x(0);
}