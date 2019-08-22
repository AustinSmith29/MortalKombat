#include "jump_right_state.h"
#include "fighter.h"

JumpRightState::JumpRightState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::JUMP)
{
}

void JumpRightState::enter(void *data)
{
	fighter.set_graphics(FighterGraphics::JUMP_FORWARD);
	fighter.jump();
	fighter.set_velocity_x(2);
	lock_input();
}

void JumpRightState::tick()
{
	if (!fighter.is_airborne())
	{
		machine.change_to(FighterStateMachine::State::IDLE, nullptr);
	}
}

void JumpRightState::exit()
{
	fighter.set_velocity_x(0);
	unlock_input();
	fighter.get_animation()->restart();
}