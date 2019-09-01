#include "stun_state.h"
#include "fighter.h"
#include "effect.h"

StunState::StunState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::NONE)
{
	effect = nullptr;
	next_state = -1;
}

void StunState::enter(void* data)
{
	lock_input();
	effect = static_cast<Effect*>(data);
	effect->enter(fighter);
	next_state = effect->get_next_state();
}

void StunState::tick()
{
	if (effect->is_complete(fighter))
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
}

void StunState::exit()
{
	effect->exit(fighter);
	effect = nullptr;
	unlock_input();
	fighter.get_animation()->restart();
}