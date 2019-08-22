#include "jump_left_state.h"
#include "fighter.h"

JumpLeftState::JumpLeftState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::JUMP)
{
}

void JumpLeftState::enter(void *data)
{
	fighter.set_graphics(FighterGraphics::JUMP_BACKWARD);
	fighter.jump();
	fighter.set_velocity_x(-2);
	lock_input();
}

void JumpLeftState::tick()
{
	if (!fighter.is_airborne())
	{
		machine.change_to(FighterStateMachine::State::IDLE, nullptr);
	}
}

void JumpLeftState::exit()
{
	fighter.set_velocity_x(0);
	unlock_input();
	fighter.get_animation()->restart();
}