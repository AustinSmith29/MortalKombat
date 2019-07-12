#include "fighter.h"

Fighter::Fighter(FighterAnimator& animator) : state_machine(*this), animator(animator)
{
	x = y = 180;
	x_vel = y_vel = 0;
	health = 100;
	orientation = Orientation::RIGHT;
}

//TODO: Can prob move these to FighterAnimator
int Fighter::topleft_x()
{
	int w = animator.get_current_animation()->get_current_frame().sheet_clip.w;
	int topleft = x - (w / 2);
	return topleft;
}

int Fighter::topleft_y()
{
	int h = animator.get_current_animation()->get_current_frame().sheet_clip.h;
	int topleft = y - h;
	return topleft;
}

Orientation Fighter::get_orientation()
{
	return orientation;
}

bones::Animation* Fighter::get_animation()
{
	return animator.get_current_animation();
}

FighterStateMachine* Fighter::get_state()
{
	return &state_machine;
}

void Fighter::set_state(FighterStateMachine::State state, void* data)
{
	state_machine.change_to(state, data);
}

void Fighter::move_left()
{
	x -= 1;
}

void Fighter::move_right()
{
	x += 1;
}

int Fighter::get_velocity_x()
{
	return x_vel;
}

void Fighter::set_velocity_x(int val)
{
	x_vel = val;
}

int Fighter::get_velocity_y()
{
	return y_vel;
}

void Fighter::set_velocity_y(int val)
{
	y_vel = val;
}

int Fighter::get_position_x()
{
	return x;
}

void Fighter::set_position_x(int val)
{
	x = val;
}

int Fighter::get_position_y()
{
	return y;
}

void Fighter::set_position_y(int val)
{
	y = val;
}

void Fighter::set_graphics(FighterGraphics graphics)
{
	animator.set_graphics(graphics);
}

void Fighter::flip_orientation()
{
	if (orientation == Orientation::LEFT)
	{
		orientation = Orientation::RIGHT;
	}
	else
	{
		orientation = Orientation::LEFT;
	}
	animator.flip_orientation();
}

void Fighter::tick()
{
	state_machine.tick();
}

void Fighter::draw(SDL_Renderer* renderer)
{
	// "Anchor" of every frame is the bottom-middle.
	// This fixes the animation jumping around on the screen. 
	int draw_x = topleft_x();
	int draw_y = topleft_y();
	animator.play(renderer, draw_x, draw_y);
}