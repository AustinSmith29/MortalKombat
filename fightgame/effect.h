#ifndef _EFFECT_H
#define _EFFECT_H

#include "fighter.h"

class Effect
{
public:
	virtual void enter(Fighter& fighter) = 0;
	virtual bool is_complete(Fighter& fighter) = 0;
	virtual void exit(Fighter& fighter) = 0;
	virtual FighterStateMachine::State get_next_state() = 0;
};

#endif