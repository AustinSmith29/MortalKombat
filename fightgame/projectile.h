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

	void kill() {
		is_alive = false;
	};
	bool is_dead() {
		return is_alive;
	};
private:
	bool is_alive{ true };
};

#endif