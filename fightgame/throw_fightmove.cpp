#include "throw_fightmove.h"
#include "thrown_effect.h"

ThrowFightMove::ThrowFightMove() : effect(new ThrownEffect())
{

}

void ThrowFightMove::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::THROW_TRY);
	this->fighter = &fighter;
}

bool ThrowFightMove::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}

void ThrowFightMove::exit(Fighter& fighter)
{
	this->fighter = nullptr;
}

void ThrowFightMove::apply_effect(Fighter& target)
{
	this->fighter->set_graphics(FighterGraphics::THROW_COMPLETE);
	target.set_state(FighterStateMachine::State::STUN, effect.get());
}
