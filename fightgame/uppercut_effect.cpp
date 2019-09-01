#include "uppercut_effect.h"

void UppercutEffect::enter(Fighter& fighter)
{
	fighter.jump();
	fighter.set_graphics(FighterGraphics::FALL);
}

bool UppercutEffect::is_complete(Fighter& fighter)
{
	return !(fighter.is_airborne());
}

void UppercutEffect::exit(Fighter& fighter)
{
}

FighterStateMachine::State UppercutEffect::get_next_state()
{
	return FighterStateMachine::State::IDLE;
}