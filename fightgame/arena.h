#ifndef _ARENA_H
#define _ARENA_H

#include <SDL.h>
#include "fighter.h"

enum ProjectileType
{
	CAGE_BLAST
};
class Arena
{
public:
	void spawn_projectile(ProjectileType type);

	void draw(SDL_Renderer* renderer);
private:
	Fighter* one;
};

#endif