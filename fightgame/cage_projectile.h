#ifndef _CAGE_PROJECTILE_H
#define _CAGE_PROJECTILE_H

#include "audio.h"
#include "standard_effect.h"
#include "projectile.h"
#include "animation.h"
#include "fighter_state.h"

#include <memory>

class CageProjectile : public Projectile
{
public:
	CageProjectile();

	CageProjectile* clone() override;
	void initialize(int x, int y, Orientation orientation) override;
	void tick() override;
	void draw(SDL_Renderer* renderer, const SDL_Rect& camera) override;
	void do_impact(Fighter& other) override;
	void load_graphics(bones::GraphicsLoader& loader) override;
	std::vector<SDL_Rect> get_dmgboxes() override;
private:
	bones::Animation projectile_animation;
	bones::Animation die_animation;
	std::shared_ptr<bones::AudioClip> sound;
	std::shared_ptr<StandardEffect> effect;
	int velocity_x;
	int velocity_y;
	const int gravity_timer{ 4 };
	int gravity_counter;
};
#endif