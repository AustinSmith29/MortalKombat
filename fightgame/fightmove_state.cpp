#include "fightmove_state.h"
#include "fighter.h"

FightMoveState::FightMoveState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::NONE)
{
	move = FightMove{};
	next_state = -1;
}

void FightMoveState::enter(void *data)
{
	lock_input();
	move = *static_cast<FightMove*>(data);
	fighter.set_graphics(move.animation);
	auto hook = machine.get_previous_state()->get_move_hook();
	if (hook == FightMoveHook::CROUCH)
	{
		next_state = FighterStateMachine::State::CROUCH;
	}
	else
	{
		next_state = FighterStateMachine::State::IDLE;
	}
}

void FightMoveState::tick()
{
	bones::Animation* animation = fighter.get_animation();
	if (fighter.get_animation()->is_complete())
	{
		unlock_input();
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
	}
}

void FightMoveState::exit()
{
	fighter.get_animation()->restart();
}