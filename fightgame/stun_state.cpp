#include "stun_state.h"
#include "fighter.h"

#include <iostream>

void StunState::enter(Fighter& fighter, FighterStateMachine& machine, void* data)
{
	std::cout << "STUN STATE ENTER!\n";
	lock_input();
	if (fighter.is_airborne())
	{
		fighter.set_graphics(FighterGraphics::FALL);
		fall = true;
		next_state = FighterStateMachine::State::IDLE;
		// knock back fighter in direction of hit
		if (fighter.get_orientation() == Orientation::RIGHT)
			fighter.set_velocity_x(-2);
		else
			fighter.set_velocity_x(2);
	}
	else if (machine.get_previous_state()->get_move_hook() == FightMoveHook::CROUCH)
	{
		fighter.set_graphics(FighterGraphics::STUN_LOW);
		next_state = FighterStateMachine::State::CROUCH;
		std::cout << "CROUCH HIT\n";
	}
	else
	{
		fighter.set_graphics(FighterGraphics::STUN_HIGH);
		next_state = FighterStateMachine::State::IDLE;
	}
}

void StunState::tick(Fighter& fighter, FighterStateMachine& machine)
{
	if (fall)
	{
		apply_gravity(fighter, machine);
		fighter.set_position_x(fighter.get_position_x() + fighter.get_velocity_x());
	}

	if (fall && has_landed(fighter))
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
	else if (fighter.get_animation()->is_complete())
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
}

void StunState::exit(Fighter& fighter, FighterStateMachine& machine)
{
	std::cout << "Exit STUN STATE\n";
	fighter.set_velocity_x(0);
	unlock_input();
	fighter.get_animation()->restart();
}