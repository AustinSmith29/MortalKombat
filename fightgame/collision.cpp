#include "collision.h"
#include "fighter.h"
#include "animation.h"

/* Hitbox/dmgbox coords are relative to top left of animation frame.
 * We must shift them to the fighters coords.
 */
static void convert_coords(std::vector<SDL_Rect>& boxes, int x, int y)
{
	for (auto& box : boxes)
	{
		box.x += x;
		box.y += y;
	}
}

bool intersects(SDL_Rect& a, SDL_Rect& b)
{
	return SDL_HasIntersection(&a, &b);
}

Collider::Collider(Fighter& owner) : fighter(owner)
{
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
	bones::Frame frame = fighter.get_animation()->get_current_frame();
	std::vector<SDL_Rect> hitboxes = frame.hitboxes;
	convert_coords(hitboxes, fighter.topleft_x(), fighter.topleft_y());
	return hitboxes;
}

std::vector<SDL_Rect> Collider::get_fighter_dmgboxes()
{
	bones::Frame frame = fighter.get_animation()->get_current_frame();
	std::vector<SDL_Rect> dmgboxes = frame.damageboxes;
	convert_coords(dmgboxes, fighter.topleft_x(), fighter.topleft_y());
	return dmgboxes;
}

void Collider::draw_boxes(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	auto hitboxes = get_fighter_hitboxes();
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
	for (auto hit : hitboxes)
		SDL_RenderFillRect(renderer, &hit);

	auto dmgboxes = get_fighter_dmgboxes();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	for (auto dmg : dmgboxes)
		SDL_RenderFillRect(renderer, &dmg);
}

