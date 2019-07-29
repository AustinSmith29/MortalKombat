#ifndef _COLLISION_H
#define _COLLISION_H

#include <SDL.h>
#include <vector>

bool intersects(const SDL_Rect& a, const SDL_Rect& b);
bool intersects(const SDL_Rect& a, const std::vector<SDL_Rect>& b);
bool intersects(const std::vector<SDL_Rect>& a, const std::vector<SDL_Rect>& b);

class Fighter;
class Projectile;
void handle_fighter_on_fighter_collision(Fighter& subject, Fighter& other);
void handle_fighter_on_projectile_collision(Fighter& subject, Projectile& other);
void draw_fighter_collision_boxes(SDL_Renderer* renderer, Fighter& fighter);
#endif