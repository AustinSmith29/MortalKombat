#include "fighter.h"

Fighter::Fighter() : move_source(this)
{
	x = y = 0;
	x_vel = y_vel = 0;
	health = 100;
	airborne = false;
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

FighterState Fighter::get_state()
{
	return state;
}

void Fighter::flip_orientation()
{

}

void Fighter::tick()
{
	switch (state.state)
	{
	case FighterState::State::STAND:
		idle_state(state.action);
		break;
	case FighterState::State::CROUCH:
		crouch_state(state.action);
		break;
	case FighterState::State::JUMP:
		jump_state(state.action);
		break;
	case FighterState::State::THROWN:
		thrown_state(state.action);
		break;
	case FighterState::State::KNOCKED:
		knocked_state(state.action);
		break;
	}
}

void Fighter::draw(SDL_Renderer* renderer)
{
	// "Anchor" of every frame is the bottom-middle.
	// This fixes the animation jumping around on the screen. 
	int draw_x = topleft_x();
	int draw_y = topleft_y();
	current_animation->play_animation(renderer, draw_x, draw_y);
}

void Fighter::handle_input_event(SDL_Event &event)
{
	move_source.process_event(event, DIRECTION_RIGHT);
	if (event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP && !airborne)
		{
			y_vel = -18;
			airborne = true;
			if (state.state == FighterState::State::JUMP && state.action == FighterState::Action::MOVERIGHT)
			{
				state = change_state(state, FighterState::State::JUMP, FighterState::Action::MOVERIGHT);
				lock_state(state);
			}
			else if (state.state == FighterState::State::JUMP && state.action == FighterState::Action::MOVELEFT)
			{
				state = change_state(state, FighterState::State::JUMP, FighterState::Action::MOVELEFT);
				lock_state(state);
			}
			else
			{
				state = change_state(state, FighterState::State::JUMP, FighterState::Action::NONE);
				lock_state(state);
			}
		}
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			state = change_state(state, FighterState::State::CROUCH, FighterState::Action::NONE);
		}
	}
	if (event.type == SDL_CONTROLLERBUTTONUP && !state.locked_action)
	{
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		{
			walk_forward.restart();
			walk_backward.restart();
			state = change_action(state, FighterState::Action::NONE);
		}
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			walk_forward.restart();
			walk_backward.restart();
			state = change_action(state, FighterState::Action::NONE);
		}
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			crouch.restart();
			state = change_state(state, FighterState::State::STAND, FighterState::Action::NONE);
		}
	}
}

void Fighter::handle_input_state(SDL_GameController* controller)
{
	if (!state.locked_state && !state.locked_action)
	{
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			state = change_action(state, FighterState::Action::MOVERIGHT);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			state = change_action(state, FighterState::Action::MOVELEFT);
		}

		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			state = change_action(state, FighterState::Action::BLOCK);
		}
	}
}

void Fighter::idle_state(FighterState::Action action)
{
	if (action == FighterState::Action::NONE)
	{
		current_animation = &idle;
	}
	else if (action == FighterState::Action::MOVERIGHT)
	{
		current_animation = &walk_forward;
		x += 1;
	}
	else if (action == FighterState::Action::MOVELEFT)
	{
		current_animation = &walk_backward;
		x -= 1;
	}
	else if (action == FighterState::Action::ATTACK)
	{
		if (current_animation->is_complete())
		{
			current_animation->restart();
			unlock_action(state);
			state = change_action(state, FighterState::Action::NONE);
			unlock_state(state);
		}
	}
}

void Fighter::crouch_state(FighterState::Action action)
{
	if (action == FighterState::Action::NONE)
	{
		current_animation = &crouch;
		if (current_animation->is_complete())
		{
			current_animation->set_pause(true);
		}
	}
	else if (action == FighterState::Action::ATTACK)
	{
		if (current_animation->is_complete())
		{
			current_animation->restart();
			state = change_action(state, FighterState::Action::NONE);
			unlock_action(state);
		}
	}
}

void Fighter::jump_state(FighterState::Action action)
{
	if (action == FighterState::Action::NONE)
	{
		x_vel = 0;
		current_animation = &jump;
		if (current_animation->is_complete())
		{
			current_animation->set_pause(true);
		}
	}
	else if (action == FighterState::Action::MOVERIGHT)
	{
		x_vel = 4;
		current_animation = &jump_move_forward;
	}
	else if (action == FighterState::Action::MOVELEFT)
	{
		x_vel = -4;
		current_animation = &jump_move_backward;
	}
	else if (action == FighterState::Action::ATTACK)
	{
		if (current_animation->is_complete())
		{
			current_animation->set_pause(true);
		}
	}
	y += y_vel;
	x += x_vel;
	y_vel += 1;
	if (y >= 350) // temporary magic value for testing
	{
		y = 350;
		y_vel = 0;
		x_vel = 0;
		airborne = false;
		unlock_state(state);
		unlock_action(state);
		state = change_state(state, FighterState::State::STAND, FighterState::Action::NONE);
		jump.restart();
		jump_move_forward.restart();
		jump_move_backward.restart();
	}
}

void Fighter::thrown_state(FighterState::Action action)
{
}

void Fighter::knocked_state(FighterState::Action action)
{
}