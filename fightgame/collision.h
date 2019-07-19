#ifndef _COLLISION_H
#define _COLLISION_H

#include <SDL.h>
#include <vector>

bool intersects(SDL_Rect& a, SDL_Rect& b);

class Fighter;
class Collider
{
public:
	Collider(Fighter& owner);

	bool hitbox_collision(SDL_Rect& other);
	bool hitbox_collision(Collider& other);

	bool damagebox_collision(SDL_Rect& other);
	bool damagebox_collision(Collider& other);

	void draw_boxes(SDL_Renderer* renderer);
private:
	Fighter& fighter;
	std::vector<SDL_Rect> get_fighter_hitboxes();
	std::vector<SDL_Rect> get_fighter_dmgboxes();
};
#endif