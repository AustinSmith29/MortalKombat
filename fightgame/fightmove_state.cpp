#include "fightmove_state.h"
#include "fighter.h"
#include "fightmove.h"

FightMoveState::FightMoveState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::NONE)
{
	move = nullptr;
	next_state = -1;
}

void FightMoveState::enter(void *data)
{
	lock_input();
	move = static_cast<FightMove*>(data);
	auto hook = machine.get_previous_state()->get_move_hook();
	if (hook == FightMoveHook::CROUCH)
	{
		next_state = FighterStateMachine::State::CROUCH;
	}
	else
	{
		next_state = FighterStateMachine::State::IDLE;
	}
	move->enter(fighter);
}

void FightMoveState::tick()
{
	if (move->is_complete(fighter))
	{
		unlock_input();
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
	}
}

void FightMoveState::exit()
{
	fighter.get_animation()->restart();
	move->exit(fighter);
	move = nullptr;
}