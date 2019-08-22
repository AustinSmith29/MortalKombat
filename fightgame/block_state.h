#ifndef _BLOCK_STATE_H
#define _BLOCK_STATE_H

#include "fighter_state.h"

class BlockState : public FighterState
{
public:
	BlockState(FighterStateMachine& machine);
	void enter(void* data) override;
	void tick() override;
	void exit() override;
};
#endif