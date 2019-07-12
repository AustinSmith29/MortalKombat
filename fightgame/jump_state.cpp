#include "jump_state.h"
#include "fighter.h"

void JumpState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
{
	fighter.set_graphics(FighterGraphics::JUMP);
	lock_input();
	start_jump(fighter);
}

void JumpState::start_jump(Fighter& fighter)
{
	lock_input();
	fighter.set_velocity_y(-10);
}

void JumpState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	apply_gravity(fighter);
}

void JumpState::apply_gravity(Fighter& fighter)
{
	decrease_y_velocity(fighter);
	update_position(fighter);
	if (has_landed(fighter))
	{
		fighter.set_velocity_y(0);
		fighter.set_position_y(FLOOR_Y_POSITION);
		finish_jump(fighter);
	}
	frame_counter++;
}

void JumpState::decrease_y_velocity(Fighter& fighter)
{
	if (frame_counter > FRAME_DELAY)
	{
		fighter.set_velocity_y(fighter.get_velocity_y() + GRAVITY);
		frame_counter = 0;
	}
}

void JumpState::update_position(Fighter& fighter)
{
	int vel = fighter.get_velocity_y();
	int old_pos = fighter.get_position_y();
	fighter.set_position_y(old_pos + vel);
}

bool JumpState::has_landed(Fighter& fighter)
{
	return fighter.get_position_y() >= FLOOR_Y_POSITION;
}

void JumpState::exit(Fighter& fighter, FighterStateMachine &machine)
{
}

void JumpState::finish_jump(Fighter& fighter)
{
	fighter.get_animation()->restart();
	unlock_input();
	fighter.reset_state();
}