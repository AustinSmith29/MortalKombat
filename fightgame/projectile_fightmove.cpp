#include "projectile_fightmove.h"

// TODO: Make Projectile Independent.
static Uint32 projectile_callback(Uint32 interval, void* param)
{
	Fighter *fighter = static_cast<Fighter*>(param);
	// if fighter has been hit before the projectile should launch... we
	// don't want it to launch.
	if (fighter->get_state()->get_state() != FighterStateMachine::State::FIGHT_MOVE) //ewww.. get_state()->get_state()
		return 0;
	auto projectile = ProjectileFactory::create(fighter->get_position_x(),
								fighter->get_position_y() - 50,
								fighter->get_orientation(),
								CAGE_PROJECTILE);
	fighter->add_projectile(std::move(projectile));
	return 0;
}

ProjectileFightMove::ProjectileFightMove(int animation, int projectile_type)
{
	this->animation = animation;
	this->projectile_type = projectile_type;
}

void ProjectileFightMove::enter(Fighter& fighter)
{
	SDL_AddTimer(450, projectile_callback, &fighter);
	fighter.set_graphics(static_cast<FighterGraphics>(this->animation));
}

bool ProjectileFightMove::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}