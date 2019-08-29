#ifndef _PROJECTILE_FIGHTMOVE_H
#define _PROJECTILE_FIGHTMOVE_H

#include "fightmove.h"
#include "projectile_factory.h"

class ProjectileFightMove : public FightMove
{
public:
	ProjectileFightMove() = default;
	ProjectileFightMove(int animation, int projectile_type);

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {}
	void apply_effect(Fighter& target) override {}
private:
	int animation;
	int projectile_type;
};

static ProjectileFightMove cage_projectile_fightmove(FighterGraphics::SPECIAL_0, 0);

#endif