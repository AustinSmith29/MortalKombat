#include "stun_state.h"
#include "fighter.h"

#include <iostream>

void StunState::enter(Fighter& fighter, FighterStateMachine& machine, void* data)
{
	if (fighter.is_airborne())
	{
		fall = true;
	}
}

void StunState::tick(Fighter& fighter, FighterStateMachine& machine)
{
	if (fall)
		apply_gravity(fighter, machine);
}

void StunState::exit(Fighter& fighter, FighterStateMachine& machine)
{
	fighter.set_graphics(FighterGraphics::STUN_LOW);
}