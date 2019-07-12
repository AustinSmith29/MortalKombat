#ifndef _BLOCK_STATE_H
#define _BLOCK_STATE_H

#include "fighter_state.h"

class BlockState : public FighterState
{
public:
	void enter(Fighter& fighter, FighterStateMachine& machine, void* data) override;
	void tick(Fighter& fighter, FighterStateMachine& machine) override;
	void exit(Fighter& fighter, FighterStateMachine& machine) override;
};
#endif