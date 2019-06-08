#ifndef _CROUCH_STATE_H
#define _CROUCH_STATE_H

#include "fighter_state.h"

class CrouchState : public FighterState
{
public:
	void enter(Fighter &fighter) override;
	void tick(Fighter &fighter) override;
	void exit(Fighter &fighter) override;
};

#endif