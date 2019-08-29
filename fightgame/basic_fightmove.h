#ifndef _BASIC_FIGHTMOVE_H
#define _BASIC_FIGHTMOVE_H

#include "fightmove.h"
#include "fighter_animator.h"

class BasicFightMove : public FightMove
{
public:
	
	BasicFightMove() = default;
	BasicFightMove(int animation, int damage); // TODO: FighterGraphics scoped wrong so it wouldn't work here... FIX.

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {};
	void apply_effect(Fighter& target) override {};

private:
	int damage;
	int animation;
};

static BasicFightMove low_punch(FighterGraphics::LOW_PUNCH, 5);
static BasicFightMove high_punch(FighterGraphics::HIGH_PUNCH, 5);
static BasicFightMove low_kick(FighterGraphics::LOW_KICK, 5);
static BasicFightMove high_kick(FighterGraphics::HIGH_KICK, 5);
static BasicFightMove crouch_kick_low(FighterGraphics::CROUCH_KICK_LOW, 5);
static BasicFightMove crouch_kick_high(FighterGraphics::CROUCH_KICK_HIGH, 5);
// THESE ARE NOT BASICFIGHTMOVES... JUST FOR TESTING
static BasicFightMove special_1(FighterGraphics::SPECIAL_1, 5);
#endif