#include "collision.h"
#include "fighter.h"
#include "animation.h"

#include <cassert>
#include <iostream>

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

static void resolve_hitbox_hitbox_collision(Fighter& subject, Fighter& other);
static int get_largest_overlap_x(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b);
static int get_largest_overlap_x(const SDL_Rect& a, const SDL_Rect& b);
void handle_fighter_on_fighter_collision(Fighter& subject, Fighter& other)
{
	auto opponent_hitboxes = get_fighter_hitboxes(other);
	auto opponent_dmgboxes = get_fighter_dmgboxes(other);
	if (is_fighter_hitbox_collision_in(subject, opponent_hitboxes))
	{
		resolve_hitbox_hitbox_collision(subject, other);
	}

	if (is_fighter_hitbox_collision_in(subject, opponent_dmgboxes))
	{
		subject.set_state(FighterStateMachine::State::STUN);
	}
}
void resolve_hitbox_hitbox_collision(Fighter& subject, Fighter& other)
{
	auto subject_hitboxes = get_fighter_hitboxes(subject);
	auto opponent_hitboxes = get_fighter_hitboxes(other);

	int dx = get_largest_overlap_x(subject_hitboxes, opponent_hitboxes);
	int subject_vel_x = subject.get_velocity_x();
	int other_vel_x = other.get_velocity_x();
	if (subject_vel_x > other_vel_x)
	{
		other.set_position_x(other.get_position_x() + dx);
	}
	else if (subject_vel_x < other_vel_x)
	{
		other.set_position_x(other.get_position_x() - dx);
	}
	else
	{
		subject.set_velocity_x(0);
		other.set_velocity_x(0);
	}
}

int get_largest_overlap_x(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b)
{
	assert(intersects(a, b));
	int largest_overlap = 0;
	for (auto a_rect : a)
	{
		for (auto b_rect : b)
		{
			largest_overlap = std::max(largest_overlap, get_largest_overlap_x(a_rect, b_rect));
		}
	}
	return largest_overlap;
}

int get_largest_overlap_x(const SDL_Rect& a, const SDL_Rect& b)
{
	assert(intersects(a, b));
	if (a.x < b.x) // left side
	{
		return a.x + a.w - b.x;
	}
	else //right side
	{
		return b.x + b.w - a.x;
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
