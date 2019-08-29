#ifndef _BASIC_FIGHTMOVE_H
#define _BASIC_FIGHTMOVE_H

#include "fightmove.h"
#include "fighter_animator.h"

class BasicFightMove : public FightMove
{
public:
	BasicFightMove(FighterGraphics animation, int damage);

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	void apply_effect(Fighter& target) override = {};

private:
	int damage;
	FighterGraphics animation;
};
#endif