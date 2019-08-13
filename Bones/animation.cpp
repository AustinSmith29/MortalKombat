#include "animation.h"

namespace bones
{
	Animation::Animation(const Sprite& sheet, const std::vector<Frame>& frames)
	{
		spritesheet = sheet;
		this->frames = frames;
	}

	const Frame& Animation::get_current_frame() const
	{
		return frames[current_frame];
	}

	void Animation::restart()
	{
		current_frame = 0;
		current_tick = 0;
	}

	void Animation::step()
	{
		Frame frame = get_current_frame();
		if (current_tick >= frame.duration)
		{
			current_frame++;
			current_tick = 0;
		}
		current_tick++;

		if (current_frame >= frames.size())
		{
			restart();
		}
	}

	void Animation::set_pause(bool value)
	{
		paused = value;
	}

	bool Animation::is_complete() const
	{
		size_t num_frames = frames.size();
		int last_duration = frames.back().duration;
		if (current_frame == num_frames - 1 && current_tick == last_duration)
			return true;
		return false;
	}

	bool Animation::is_paused() const
	{
		return paused;
	}

	Animation Animation::reverse()
	{
		Animation reversed = *this;
		std::reverse(reversed.frames.begin(), reversed.frames.end());
		return reversed;
	}

	static SDL_Rect flip_rect_on_x_axis(const SDL_Rect& rect, int axis);
	Animation Animation::flip()
	{
		if (flip_status == SDL_FLIP_HORIZONTAL)
			flip_status = SDL_FLIP_NONE;
		else
			flip_status = SDL_FLIP_HORIZONTAL;

		for (auto& frame : frames)
		{
			int center = frame.sheet_clip.w / 2;
			// flip hboxes and dboxes along center
			for (auto& dbox : frame.damageboxes)
			{
				dbox = flip_rect_on_x_axis(dbox, center);
			}
			for (auto& hbox : frame.hitboxes)
			{
				hbox = flip_rect_on_x_axis(hbox, center);
			}
		}
		return *this; // TODO: change this obviously
	}

	static SDL_Rect flip_rect_on_x_axis(const SDL_Rect& rect, int axis)
	{
		return SDL_Rect{
			(-rect.x + 2 * axis) - rect.w, // -rect.w because x is left-most point
			rect.y,
			rect.w,
			rect.h
		};
	}

	void Animation::play_animation(SDL_Renderer * renderer, int x, int y)
	{
		draw_single_frame(renderer, x, y);
		if (!is_complete())
			step();
	}

	void Animation::loop()
	{
		if (is_complete())
		{
			restart();
		}
	}

	void Animation::draw_single_frame(SDL_Renderer * renderer, int x, int y)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		Frame frame = get_current_frame();
		rect.w = frame.sheet_clip.w;
		rect.h = frame.sheet_clip.h;

		SDL_RenderCopyEx(renderer, spritesheet.texture.get(), &frame.sheet_clip, &rect, 0.0f, nullptr, flip_status);
	}
}
