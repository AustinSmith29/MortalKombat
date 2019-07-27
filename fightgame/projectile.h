#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <SDL.h>

class Fighter;
class Projectile
{
public:
	virtual ~Projectile() = default;

	virtual void tick() = 0;
	virtual void draw(SDL_Renderer* renderer);
	virtual void do_impact(Fighter& other);
};

#endif