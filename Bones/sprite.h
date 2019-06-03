#ifndef _SPRITE_H
#define _SPRITE_H

#include <SDL.h>
#include <memory>

namespace bones
{
	struct Sprite
	{
		Sprite() = default;
		Sprite(std::shared_ptr<SDL_Texture> texture);

		std::shared_ptr<SDL_Texture> texture; 
	};

	void draw_sprite(SDL_Renderer* renderer, Sprite& sprite, int x, int y);
}
#endif