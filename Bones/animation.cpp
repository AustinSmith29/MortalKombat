#include "animation.h"

namespace bones
{
	Animation::Animation(Sprite sheet, std::vector<Frame> frames)
	{
		spritesheet = sheet;
		this->frames = frames;
	}

	const Frame& Animation::get_current_frame()
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

	Animation Animation::flip()
	{
		flip_status = SDL_FLIP_HORIZONTAL;
		for (auto frame : frames)
		{
			// flip hboxes and dboxes along center
			continue;
		}
	}

	void Animation::play_animation(SDL_Renderer * renderer, int x, int y)
	{
		draw_single_frame(renderer, x, y);
		step();
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
