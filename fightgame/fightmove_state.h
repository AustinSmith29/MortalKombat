#ifndef _FIGHTMOVE_STATE_H
#define _FIGHTMOVE_STATE_H

#include "fighter_state.h"

class FightMove;
class FightMoveState : public FighterState
{
public:
	FightMoveState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
private:
	int next_state;
	FightMove* move;
};
#endif