#include "cage.h"

#include <iostream>

#define ANIMATIONS "data/johnnycage/animations/"

void JohnnyCage::load_resources(bones::GraphicsLoader& loader)
{
	idle = loader.load_animation(ANIMATIONS "cage_idle.xml");
	crouch = loader.load_animation(ANIMATIONS "cage_crouch.xml");
	jump = loader.load_animation(ANIMATIONS "cage_jump_up.xml");
	jump_move_forward = loader.load_animation(ANIMATIONS "cage_jump_move.xml");
	jump_move_backward = jump_move_forward.reverse();
	walk_forward = loader.load_animation(ANIMATIONS "cage_walk.xml");
	walk_backward = walk_forward.reverse();

	//move_source.bind_owner(this);
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
