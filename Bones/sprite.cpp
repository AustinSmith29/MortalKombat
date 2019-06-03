#include "sprite.h"

#include <stdexcept>

namespace bones
{
	Sprite::Sprite(std::shared_ptr<SDL_Texture> texture)
	{
		if (!texture)
			throw std::runtime_error("Could not construct Sprite!");
		this->texture = texture;
	}

	void draw_sprite(SDL_Renderer* renderer, Sprite& sprite, int x, int y)
	{
		// NULL, NULL just to verify everything is working at first.
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(sprite.texture.get(), NULL, NULL, &rect.w, &rect.h);
		SDL_RenderCopy(renderer, sprite.texture.get(), NULL, &rect);
	}
}
