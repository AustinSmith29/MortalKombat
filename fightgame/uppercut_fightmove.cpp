#include "uppercut_fightmove.h"

UppercutFightMove::UppercutFightMove() : effect(std::make_unique<UppercutEffect>())
{
	damage = 0;
}

UppercutFightMove::UppercutFightMove(int damage) : 
	effect(std::make_unique<UppercutEffect>())

{
	this->damage = damage;
}

void UppercutFightMove::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::UPPERCUT);
}

bool UppercutFightMove::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}

void UppercutFightMove::apply_effect(Fighter& target)
{
	target.set_state(FighterStateMachine::State::STUN, effect.get());
}
