#include "collision.h"
#include "fighter.h"

bool intersects(SDL_Rect& a, SDL_Rect& b)
{
	return false;
}

Collider::Collider(Fighter* owner)
{
	fighter = owner;
}

bool collision_in(std::vector<SDL_Rect>& vec, SDL_Rect& other)
{
	for (auto box : vec)
	{
		if (intersects(box, other))
			return true;
	}
	return false;
}

bool Collider::hitbox_collision(SDL_Rect& other)
{
	auto hitboxes = get_fighter_hitboxes();
	return collision_in(hitboxes, other);
}

bool Collider::hitbox_collision(Collider& other)
{
	auto other_dmgboxes = other.get_fighter_dmgboxes();
	for (auto dmgbox : other_dmgboxes)
	{
		if (hitbox_collision(dmgbox))
			return true;
	}
	return false;
}

bool Collider::damagebox_collision(SDL_Rect& other)
{
	auto dmgboxes = get_fighter_dmgboxes();
	return collision_in(dmgboxes, other);
}

bool Collider::damagebox_collision(Collider& other)
{
	auto other_hitboxes = other.get_fighter_hitboxes();
	for (auto hitbox : other_hitboxes)
	{
		if (damagebox_collision(hitbox))
			return true;
	}
	return false;
}

std::vector<SDL_Rect> Collider::get_fighter_hitboxes()
{
	std::vector<SDL_Rect> hitboxes;
	int current_frame = fighter->current_animation->current_frame;
	auto hitboxes_map = fighter->current_animation->hitboxes;
	if (hitboxes_map.find(current_frame) != hitboxes_map.end())
		hitboxes = hitboxes_map[current_frame];
	return hitboxes;
}

std::vector<SDL_Rect> Collider::get_fighter_dmgboxes()
{
	std::vector<SDL_Rect> dmgboxes;
	int current_frame = fighter->current_animation->current_frame;
	auto dmgboxes_map = fighter->current_animation->dmgboxes;
	if (dmgboxes_map.find(current_frame) != dmgboxes_map.end())
		dmgboxes = dmgboxes_map[current_frame];
	return dmgboxes;
}
