#include "cage.h"

#include <iostream>

#define ANIMATIONS "data/johnnycage/animations/"

void JohnnyCage::load_resources(bones::GraphicsLoader& loader)
{
	idle = loader.load_animation(ANIMATIONS "cage_idle.xml");
	crouch = loader.load_animation(ANIMATIONS "cage_crouch.xml");
	jump = loader.load_animation(ANIMATIONS "cage_jump_up.xml");
	jump_move_forward = loader.load_animation(ANIMATIONS "cage_jump_move.xml");
	jump_move_backward = bones::reverse_animation(jump_move_forward);
	walk_forward = loader.load_animation(ANIMATIONS "cage_walk.xml");
	walk_backward = bones::reverse_animation(walk_forward);

	move_source.bind_owner(this);
	move_source.load_moves_from_file("data/johnnycage/moves.xml", loader);
	FighterState initial = FighterState(FighterState::State::STAND, FighterState::Action::NONE, 
		FighterState::Orientation::RIGHT);
	current_animation = &idle;
	state = initial;
	x = 150;
	y = 350;
	airborne = false;
	x_vel = y_vel = 0;
}

void JohnnyCage::handle_input_event(SDL_Event &event)
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
			bones::restart_animation(walk_forward);
			bones::restart_animation(walk_backward);
			state = change_action(state, FighterState::Action::NONE);
		}
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		{
			bones::restart_animation(walk_forward);
			bones::restart_animation(walk_backward);
			state = change_action(state, FighterState::Action::NONE);
		}
		if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
		{
			bones::restart_animation(crouch);
			state = change_state(state, FighterState::State::STAND, FighterState::Action::NONE);
		}
	}
}

void JohnnyCage::handle_input_state(SDL_GameController* controller)
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

void JohnnyCage::process_move(Move& move)
{
	current_animation = &move.animation;
	if (move.name == "jump_move_right")
	{
		state = change_state(state, FighterState::State::JUMP, FighterState::Action::MOVERIGHT);
		lock_state(state);
		return;
	}
	if (move.name == "jump_move_left")
	{
		state = change_state(state, FighterState::State::JUMP, FighterState::Action::MOVELEFT);
		lock_state(state);
		return;
	}
	std::cout << move.name << std::endl;
	state = change_action(state, FighterState::Action::ATTACK);
	lock_state(state);
	lock_action(state);
}

void JohnnyCage::flip_orientation()
{
	bones::flip_animation(idle);
	bones::flip_animation(walk_backward);
	bones::flip_animation(walk_forward);
}

void JohnnyCage::idle_state(FighterState::Action action)
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
		if (bones::is_animation_complete(*current_animation))
		{
			bones::restart_animation(*current_animation);
			unlock_action(state);
			state = change_action(state, FighterState::Action::NONE);
			unlock_state(state);
		}
	}
}

void JohnnyCage::crouch_state(FighterState::Action action)
{
	if (action == FighterState::Action::NONE)
	{
		current_animation = &crouch;
		if (bones::is_animation_complete(*current_animation))
		{
			bones::pause_animation(*current_animation);
		}
	}
	else if (action == FighterState::Action::ATTACK)
	{
		if (bones::is_animation_complete(*current_animation))
		{
			bones::restart_animation(*current_animation);
			state = change_action(state, FighterState::Action::NONE);
			unlock_action(state);
		}
	}
}

void JohnnyCage::jump_state(FighterState::Action action)
{
	if (action == FighterState::Action::NONE)
	{
		x_vel = 0;
		current_animation = &jump;
		if (bones::is_animation_complete(*current_animation))
		{
			bones::pause_animation(*current_animation);
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
		if (bones::is_animation_complete(*current_animation))
		{
			bones::pause_animation(*current_animation);
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
		bones::restart_animation(jump);
		bones::restart_animation(jump_move_forward);
		bones::restart_animation(jump_move_backward);
	}
}

void JohnnyCage::thrown_state(FighterState::Action action)
{
}

void JohnnyCage::knocked_state(FighterState::Action action)
{
}
