#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include <SDL.h>
#include "graphics.h"
#include "fighter_state.h"

class Fighter;
class Projectile
{
public:
	virtual ~Projectile() = default;

	virtual Projectile* clone() = 0;
	virtual void initialize(int x, int y, Orientation direction) = 0;
	virtual void tick() = 0;
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void do_impact(Fighter& other) {};
	virtual void load_graphics(bones::GraphicsLoader& loader) = 0;

	void kill() {
		is_alive = false;
	};
	bool is_dead() {
		return !is_alive;
	};
	void set_position(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void set_direction(Orientation direction) {
		this->direction = direction;
	}
protected:
	int damage{ 0 };
	int x{ 0 };
	int y{ 0 };
	Orientation direction;
private:
	bool is_alive{ true };
};

#endif