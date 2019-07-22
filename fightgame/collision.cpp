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

bool intersects(const SDL_Rect& a, const SDL_Rect& b)
{
	return SDL_HasIntersection(&a, &b);
}

bool intersects(const SDL_Rect& a, const std::vector<SDL_Rect>& b)
{
	for (auto rect : b)
	{
		if (intersects(a, rect))
			return true;
	}
	return false;
}

bool intersects(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b)
{
	for (auto rect : a)
	{
		if (intersects(rect, b))
			return true;
	}
	return false;
}

static std::vector<SDL_Rect> get_fighter_hitboxes(Fighter& fighter);
static std::vector<SDL_Rect> get_fighter_dmgboxes(Fighter& fighter);
static bool is_fighter_hitbox_collision_in(Fighter& fighter, const std::vector<SDL_Rect>& boxes)
{
	auto hitboxes = get_fighter_hitboxes(fighter);
	return intersects(hitboxes, boxes);
}

static bool is_fighter_damagebox_collision_in(Fighter& fighter, const std::vector<SDL_Rect>& boxes)
{
	auto dmgboxes = get_fighter_dmgboxes(fighter);
	return intersects(dmgboxes, boxes);
}

std::vector<SDL_Rect> get_fighter_hitboxes(Fighter& fighter)
{
	bones::Frame frame = fighter.get_animation()->get_current_frame();
	std::vector<SDL_Rect> hitboxes = frame.hitboxes;
	convert_coords(hitboxes, fighter.topleft_x(), fighter.topleft_y());
	return hitboxes;
}

std::vector<SDL_Rect> get_fighter_dmgboxes(Fighter& fighter)
{
	bones::Frame frame = fighter.get_animation()->get_current_frame();
	std::vector<SDL_Rect> dmgboxes = frame.damageboxes;
	convert_coords(dmgboxes, fighter.topleft_x(), fighter.topleft_y());
	return dmgboxes;
}

void handle_fighter_on_fighter_collision(Fighter& subject, Fighter& other)
{
	auto opponent_dmgboxes = get_fighter_dmgboxes(other);
	if (is_fighter_hitbox_collision_in(subject, opponent_dmgboxes))
	{
		subject.set_state(FighterStateMachine::State::BLOCK);
	}
}

void draw_fighter_collision_boxes(SDL_Renderer* renderer, Fighter& fighter)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	auto hitboxes = get_fighter_hitboxes(fighter);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
	for (auto hit : hitboxes)
		SDL_RenderFillRect(renderer, &hit);

	auto dmgboxes = get_fighter_dmgboxes(fighter);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	for (auto dmg : dmgboxes)
		SDL_RenderFillRect(renderer, &dmg);
}
