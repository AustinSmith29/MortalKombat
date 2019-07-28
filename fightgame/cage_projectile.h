#ifndef _CAGE_PROJECTILE_H
#define _CAGE_PROJECTILE_H

#include "projectile.h"
#include "animation.h"
#include "fighter_state.h"

class CageProjectile : public Projectile
{
public:
	CageProjectile(int x, int y, Orientation direction);

	CageProjectile* clone() override;
	void tick() override;
	void draw(SDL_Renderer* renderer) override;
	void do_impact(Fighter& other) override;
	void load_graphics(bones::GraphicsLoader& loader) override;
private:
	bones::Animation projectile_animation;
	bones::Animation die_animation;
	int velocity_x;
	int velocity_y;
	const int gravity_timer{ 4 };
	int gravity_counter;
};
#endif