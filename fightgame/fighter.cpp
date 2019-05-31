#include "fighter.h"


FighterState Fighter::get_state()
{
	return state;
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
	int w = current_animation->frames[current_animation->current_frame].w;
	int h = current_animation->frames[current_animation->current_frame].h;
	int draw_x = x - (w / 2);
	int draw_y = y - h;
	bones::play_animation(renderer, *current_animation, draw_x, draw_y);
}

void Fighter::hit()
{
	if (state.action != FighterState::Action::BLOCK)
	{
		state = change_action(state, FighterState::Action::STUN);
	}
}