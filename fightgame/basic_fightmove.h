#ifndef _BASIC_FIGHTMOVE_H
#define _BASIC_FIGHTMOVE_H

#include "fightmove.h"
#include "fighter_animator.h"

#include <memory>

class Effect;
class BasicFightMove : public FightMove
{
public:
	
	BasicFightMove() = default;
	// TODO: FighterGraphics scoped wrong so it wouldn't work here... FIX.
	BasicFightMove(int animation, int damage, std::shared_ptr<Effect> effect); 

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {};
	void apply_effect(Fighter& target) override;

private:
	int damage;
	int animation;
	std::shared_ptr<Effect> effect;
};
#endif