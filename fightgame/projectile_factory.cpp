#include "projectile_factory.h"
#include "cage_projectile.h"

namespace ProjectileFactory
{
	static std::array<std::unique_ptr<Projectile>, PROJECTILE_TOTAL> prototypes = {
		std::make_unique<CageProjectile>(0, 0, Orientation::LEFT),
	};

	void load(bones::GraphicsLoader& loader)
	{
		prototypes[CAGE_PROJECTILE]->load_graphics(loader);
	}

	std::unique_ptr<Projectile> create(int x, int y, Orientation direction, ProjectileType type)
	{
		std::unique_ptr<Projectile> projectile(prototypes[type]->clone());
		projectile->set_position(x, y);
		projectile->set_direction(direction);
		return projectile;
	}
}