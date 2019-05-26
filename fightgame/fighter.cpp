#include "fighter.h"
#include <iostream>

Fighter::Fighter(bones::GraphicsLoader &loader) 
	: moveSource(this)
{
	moveSource.load_moves_from_file("data/johnnycage/moves.xml", loader);
	idle = loader.load_animation("data/johnnycage/animations/cage_idle.xml");
	walk = loader.load_animation("data/johnnycage/animations/cage_walk.xml");
	x = 100;
	y = 300;
	state = IDLE;
	current_animation = &idle;
}

void Fighter::process_move(Move& move)
{
	current_animation = &move.animation;
	change_state(MOVE);
	if (move.name == "fireball")
	{
		std::cout << "Spawning fireball" << std::endl;
	}
}

void Fighter::read_moves(SDL_Event& event)
{
	moveSource.process_event(event, DIRECTION_RIGHT);
	if (event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		if (state == WALK)
			change_state(IDLE);
	}
	if (event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		if (state == WALK)
			change_state(IDLE);
	}
}

void Fighter::handle_input(SDL_GameController* controller)
{
	if (state != MOVE)
	{
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			x += 1;
			change_state(WALK);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			x -= 1;
			change_state(WALK);
		}
		else
		{
			//change_state(IDLE);
		}
	}
}

void Fighter::tick()
{
	switch (state)
	{
	case IDLE:
		current_animation = &idle;
		break;
	case WALK:
		current_animation = &walk;
		break;
	case MOVE:
		if (bones::is_animation_complete(*current_animation))
		{
			bones::restart_animation(*current_animation);
			change_state(IDLE);
		}
		break;
	}
}

void Fighter::draw(SDL_Renderer* renderer)
{
	bones::play_animation(renderer, *current_animation, x, y);
}

void Fighter::change_state(State to)
{
	State from = state;
	switch (from)
	{
	case IDLE:
		// idle can go into any state
		state = to;
		break;
	case BLOCK:
		if (to != MOVE)
			state = to;
		break;
	case JUMP:
		if (to != JUMP && to != BLOCK && to != JUMP)
			state = to;
		break;
	case DUCK:
		if (to != JUMP)
			state = to;
		break;
	case WALK:
		state = to;
		break;
	case MOVE:
		if (to == IDLE)
			state = to;
		break;
	}
}