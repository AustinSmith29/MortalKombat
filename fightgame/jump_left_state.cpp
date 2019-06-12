#include "jump_left_state.h"
#include "fighter.h"

void JumpLeftState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::JUMP_BACKWARD);
	start_jump(fighter);
}

void JumpLeftState::tick(Fighter& fighter)
{
	apply_gravity(fighter);
	if (!has_landed(fighter))
	{
		fighter.move_left();
	}
}

void JumpLeftState::exit(Fighter& fighter)
{
}

void JumpLeftState::update_position(Fighter& fighter)
{
	int vel = fighter.get_velocity_y();
	int old_pos = fighter.get_position_y();
	fighter.set_position_y(old_pos + vel);
	fighter.move_left();
}