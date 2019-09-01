#ifndef _UPPERCUT_FIGHTMOVE
#define _UPPERCUT_FIGHTMOVE

#include "fightmove.h"
#include "uppercut_effect.h"
#include <memory>

class UppercutFightMove : public FightMove
{
public:
	UppercutFightMove();
	UppercutFightMove(int damage);

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {};
	void apply_effect(Fighter& fighter) override;
private:
	int damage;
	std::unique_ptr<UppercutEffect> effect;
};

#endif