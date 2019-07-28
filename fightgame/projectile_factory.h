#ifndef _PROJECTILE_FACTORY_H
#define _PROJECTILE_FACTORY_H

#include "projectile.h"
#include "fighter_state.h"

#include <array>
#include <memory>

enum ProjectileType
{
	CAGE_PROJECTILE,
	PROJECTILE_TOTAL,
};

namespace ProjectileFactory
{
	void load(bones::GraphicsLoader& loader);
	std::unique_ptr<Projectile> create(int x, int y, Orientation direction, ProjectileType type);
};
#endif