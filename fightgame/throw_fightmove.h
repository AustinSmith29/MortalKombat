#ifndef _THROW_FIGHTMOVE_H
#define _THROW_FIGHTMOVE_H

#include "fightmove.h"
#include <memory>

class ThrownEffect;
class ThrowFightMove : public FightMove
{
public:
	ThrowFightMove();
	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	void apply_effect(Fighter& target) override;
private:
	Fighter* fighter;
	std::unique_ptr<ThrownEffect> effect;
};
#endif