#ifndef _FIGHTMOVE_STATE_H
#define _FIGHTMOVE_STATE_H

#include "fightmove_state.h"

class FightMoveState : public FighterState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
};
#endif