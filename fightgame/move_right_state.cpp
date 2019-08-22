#include "move_right_state.h"
#include "fighter.h"

MoveRightState::MoveRightState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::STAND)
{
}

void MoveRightState::enter(void *data)
{
	if (fighter.get_orientation() == Orientation::RIGHT)
	{
		fighter.set_graphics(FighterGraphics::WALK_FORWARD);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::WALK_BACKWARD);
	}
	fighter.set_velocity_x(1);
}

void MoveRightState::tick()
{
	fighter.get_animation()->loop();
}

void MoveRightState::exit()
{
	fighter.set_velocity_x(0);
}