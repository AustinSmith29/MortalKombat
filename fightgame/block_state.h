#ifndef _BLOCK_STATE_H
#define _BLOCK_STATE_H

#include "fighter_state.h"

class BlockState : public FighterState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
};
#endif