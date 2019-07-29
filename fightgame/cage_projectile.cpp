#include "cage_projectile.h"
#include "constants.h"

CageProjectile::CageProjectile()
{
	damage = 10;
}

void CageProjectile::initialize(int x, int y, Orientation direction)
{
	this->x = x;
	this->y = y;
	this->direction = direction;
	if (direction == Orientation::LEFT) 
		velocity_x = -8;
	else
		velocity_x = 8;
	velocity_y = -4;
	gravity_counter = 0;
}

CageProjectile* CageProjectile::clone()
{
	return new CageProjectile(*this);
}

void CageProjectile::tick()
{
	gravity_counter++;
	if (gravity_counter > gravity_timer)
	{ 
		velocity_y += GRAVITY;
		gravity_counter = 0;
	}

	x += velocity_x;
	y += velocity_y;

	if (y >= FLOOR_Y)
		kill();
}

void CageProjectile::draw(SDL_Renderer* renderer)
{
	if (is_dead())
	{
		die_animation.play_animation(renderer, x, y);
	}
	else
	{
		projectile_animation.play_animation(renderer, x, y);
	}
}

void CageProjectile::do_impact(Fighter& other)
{
	kill();
}

void CageProjectile::load_graphics(bones::GraphicsLoader& loader)
{
	projectile_animation = loader.load_animation("data/johnnycage/animations/cage_projectile.xml");
	die_animation = loader.load_animation("data/johnnycage/animations/cage_projectile_explode.xml");
}