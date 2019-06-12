#include "fighter.h"
#include <iostream>

Fighter::Fighter() : move_source(this)
{
	x = y = 0;
	x_vel = y_vel = 0;
	health = 100;
	current_state = &idle_state;
	current_animation = nullptr;
	orientation = Orientation::RIGHT;
	set_graphics_map();
}

void Fighter::set_graphics_map()
{
	graphics_map[FighterGraphics::IDLE] = &idle;
	graphics_map[FighterGraphics::WALK_FORWARD] = &walk_forward;
	graphics_map[FighterGraphics::WALK_BACKWARD] = &walk_backward;
	graphics_map[FighterGraphics::CROUCH] = &crouch;
	graphics_map[FighterGraphics::JUMP] = &jump;
	graphics_map[FighterGraphics::JUMP_FORWARD] = &jump_forward;
	graphics_map[FighterGraphics::JUMP_BACKWARD] = &jump_backward;
}

int Fighter::topleft_x()
{
	int w = current_animation->get_current_frame().sheet_clip.w;
	int topleft = x - (w / 2);
	return topleft;
}

int Fighter::topleft_y()
{
	int h = current_animation->get_current_frame().sheet_clip.h;
	int topleft = y - h;
	return topleft;
}

Orientation Fighter::get_orientation()
{
	return orientation;
}

FighterState::FightMoveHook Fighter::get_fight_move_hook()
{
	return current_state->get_move_hook();
}

bones::Animation* Fighter::get_animation()
{
	return current_animation;
}

void Fighter::move_left()
{
	x -= 1;
}

void Fighter::move_right()
{
	x += 1;
}

int Fighter::get_velocity_y()
{
	return y_vel;
}

void Fighter::set_velocity_y(int val)
{
	y_vel = val;
}

int Fighter::get_position_y()
{
	return y;
}

void Fighter::set_position_y(int val)
{
	y = val;
}
void Fighter::perform_fight_move(bones::Animation& move)
{
	graphics_map[FighterGraphics::FIGHT_MOVE] = &move;
	change_state_if_open(&fightmove_state);
}

void Fighter::set_graphics(FighterGraphics graphics)
{
	current_animation = graphics_map[graphics];
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
}

void Fighter::reset_state()
{
	set_state(&idle_state);
}

void Fighter::tick()
{
	current_state->tick(*this);
}

void Fighter::draw(SDL_Renderer* renderer)
{
	// "Anchor" of every frame is the bottom-middle.
	// This fixes the animation jumping around on the screen. 
	int draw_x = topleft_x();
	int draw_y = topleft_y();
	current_animation->play_animation(renderer, draw_x, draw_y);
}

void Fighter::handle_input_event(SDL_Event &event, SDL_GameController *controller)
{
	if (current_state->is_input_locked())
		return;
	move_source.process_event(event, orientation);
	if (event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		handle_button_press(event.cbutton.button, controller);
	}
	if (event.type == SDL_CONTROLLERBUTTONUP)
	{
		handle_button_release(event.cbutton.button);
	}
}

void Fighter::handle_button_press(Uint8 button, SDL_GameController *controller)
{
	if (button == SDL_CONTROLLER_BUTTON_DPAD_UP)
	{
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			change_state_if_open(&jump_right_state);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			change_state_if_open(&jump_left_state);
		}
		else
		{
			change_state_if_open(&jump_state);
		}
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		change_state_if_open(&move_right_state);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		change_state_if_open(&move_left_state);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
	{
		change_state_if_open(&crouch_state);
	}
}

void Fighter::handle_button_release(Uint8 button)
{
	change_state_if_open(&idle_state);
}

void Fighter::handle_input_state(SDL_GameController* controller)
{
}

void Fighter::change_state_if_open(FighterState* to)
{
	set_state(to);
}

void Fighter::set_state(FighterState* to)
{
	current_state->exit(*this);
	current_state = to;
	current_state->enter(*this);
}