#include "uppercut_fightmove.h"

UppercutFightMove::UppercutFightMove(int damage)
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
	target.jump();
}
