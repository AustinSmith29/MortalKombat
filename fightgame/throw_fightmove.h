#ifndef _THROW_FIGHTMOVE_H
#define _THROW_FIGHTMOVE_H

#include "fightmove.h"

class ThrowFightMove : public FightMove
{
public:
	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	void apply_effect(Fighter& target) override;
private:
	Fighter* fighter;
};
#endif