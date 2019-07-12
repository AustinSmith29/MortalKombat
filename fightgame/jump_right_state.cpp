#include "jump_right_state.h"
#include "fighter.h"

void JumpRightState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
{
	fighter.set_graphics(FighterGraphics::JUMP_FORWARD);
	start_jump(fighter);
}

void JumpRightState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	apply_gravity(fighter, machine);
	if (!has_landed(fighter))
	{
		fighter.move_right();
	}
}

void JumpRightState::exit(Fighter& fighter, FighterStateMachine &machine)
{
}

void JumpRightState::update_position(Fighter& fighter)
{
	int vel = fighter.get_velocity_y();
	int old_pos = fighter.get_position_y();
	fighter.set_position_y(old_pos + vel);
	fighter.move_right();
}