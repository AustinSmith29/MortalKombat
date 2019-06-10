#include "jump_state.h"
#include "fighter.h"

void JumpState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::JUMP);
	lock_input();
	fighter.set_velocity_y(-10);
	is_airborne = true;
}

void JumpState::tick(Fighter& fighter)
{
	int vel = fighter.get_velocity_y();
	int y = fighter.get_position_y();
	if (frame_counter > FRAME_DELAY)
	{
		fighter.set_velocity_y(vel + GRAVITY);
		frame_counter = 0;
	}

	y += vel;
	fighter.set_position_y(y);

	if (y >= FLOOR_Y_POSITION)
	{
		fighter.set_velocity_y(0);
		fighter.set_position_y(FLOOR_Y_POSITION);
		exit(fighter);
	}
	frame_counter++;
}

void JumpState::exit(Fighter& fighter)
{
	fighter.get_animation()->restart();
	unlock_input();
	fighter.set_graphics(FighterGraphics::IDLE);
	is_airborne = false;
}