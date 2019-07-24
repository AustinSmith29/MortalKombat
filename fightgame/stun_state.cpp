#include "stun_state.h"
#include "fighter.h"

void StunState::enter(Fighter& fighter, FighterStateMachine& machine, void* data)
{
	fighter.set_graphics(FighterGraphics::STUN_HIGH);
}

void StunState::tick(Fighter& fighter, FighterStateMachine& machine)
{
}

void StunState::exit(Fighter& fighter, FighterStateMachine& machine)
{
	fighter.set_graphics(FighterGraphics::STUN_LOW);
}