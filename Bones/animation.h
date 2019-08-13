#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "sprite.h"

#include <SDL.h>
#include <vector>

namespace bones
{
	struct Frame
	{
		SDL_Rect sheet_clip;
		unsigned int duration{ 1 };
		std::vector<SDL_Rect> hitboxes;
		std::vector<SDL_Rect> damageboxes;
	};

	class Animation
	{
	public:
		Animation() = default;
		Animation(const Sprite& sheet, const std::vector<Frame>& frames);

		const Frame& get_current_frame() const;

		void restart();
		void step();
		void set_pause(bool value);

		bool is_complete() const;
		bool is_paused() const;

		Animation reverse();
		Animation flip();

		void play_animation(SDL_Renderer* renderer, int x, int y);
		void loop();

	private:
		Sprite spritesheet;
		std::vector<Frame> frames;
		int current_frame{ 0 };
		unsigned int current_tick{ 0 };
		bool paused{ false };
		SDL_RendererFlip flip_status{ SDL_FLIP_NONE };

		void draw_single_frame(SDL_Renderer* renderer, int x, int y);
	};
}
#endif