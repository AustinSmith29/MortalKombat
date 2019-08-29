#ifndef _FIGHTMOVE_H
#define _FIGHTMOVE_H

#include "fighter.h"

class Effect;
class FightMove
{
public:
	virtual ~FightMove() = default;
	virtual void enter(Fighter& fighter) = 0;
	virtual bool is_complete(Fighter& fighter) = 0;
	virtual void exit(Fighter& fighter) = 0;
	virtual void apply_effect(Fighter& target) = 0;
};
#endif