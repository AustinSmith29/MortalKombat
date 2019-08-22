#include "stun_state.h"
#include "fighter.h"

StunState::StunState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::NONE)
{
}

void StunState::enter(void* data)
{
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
	}
	else
	{
		fighter.set_graphics(FighterGraphics::STUN_HIGH);
		next_state = FighterStateMachine::State::IDLE;
	}
}

void StunState::tick()
{
	if (fall && !fighter.is_airborne())
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
	else if (!fall && fighter.get_animation()->is_complete())
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
}

void StunState::exit()
{
	fighter.set_velocity_x(0);
	unlock_input();
	fighter.get_animation()->restart();
}