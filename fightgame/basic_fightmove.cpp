#include "basic_fightmove.h"

BasicFightMove::BasicFightMove(int animation, int damage)
{
	this->animation = animation;
	this->damage = damage;
}

void BasicFightMove::enter(Fighter& fighter)
{
	fighter.set_graphics(static_cast<FighterGraphics>(this->animation));
}

bool BasicFightMove::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}
