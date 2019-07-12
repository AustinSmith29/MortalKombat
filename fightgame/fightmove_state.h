#ifndef _FIGHTMOVE_STATE_H
#define _FIGHTMOVE_STATE_H

#include "fighter_state.h"
#include "fightmove.h"

class FightMoveState : public FighterState
{
public:
	void enter(Fighter& fighter, FighterStateMachine &machine, void *data) override;
	void tick(Fighter& fighter, FighterStateMachine &machine) override;
	void exit(Fighter& fighter, FighterStateMachine &machine) override;
private:
	FightMove move;
};
#endif