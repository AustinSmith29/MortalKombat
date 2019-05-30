#include "graphics.h"
#include "rapidxml.hpp"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> //std::reverse

using namespace rapidxml;

namespace bones
{
	struct AnimationFileData
	{
		std::string sheetpath;
		std::vector<SDL_Rect> frames;
		std::vector<SDL_Rect> hitboxes;
		std::vector<SDL_Rect> dmgboxes;
		std::vector<int>      durations;
	};

	// Helper function for GraphicsLoader::load_animation
	AnimationFileData parse_animation_file(std::string filepath);

	void
	GraphicsLoader::register_service(SDL_Renderer* renderer)
	{
		this->renderer = renderer;
	}

	std::unique_ptr<Sprite>
	GraphicsLoader::load_sprite(std::string filepath)
	{
		if (!renderer)
			throw std::runtime_error("GraphicsLoader has not been registered!");

		// Retrieve texture if it has been loaded before.
		auto it = registry.find(filepath);
		if (it != registry.end())
		{
			auto texture = registry[filepath];
			auto new_sprite = std::make_unique<Sprite>(texture);
			return new_sprite;
		}

		// Else load it for first time.
		SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
		if (!surface)
		{
			std::cout << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!texture)
		{
			std::cout << SDL_GetError() << std::endl;
			return nullptr;
		}

		SDL_FreeSurface(surface);
		registry[filepath] = std::shared_ptr<SDL_Texture>(texture,
			[](SDL_Texture * t)
			{
				SDL_DestroyTexture(t);
			});
		auto new_sprite = std::make_unique<Sprite>(registry[filepath]);
		return new_sprite;
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

	Animation
	GraphicsLoader::load_animation(std::string filepath)
	{
		if (!renderer)
			throw std::runtime_error("GraphicsLoader has not been registered!");

		AnimationFileData anim_data = parse_animation_file(filepath);
		auto sheet = load_sprite(anim_data.sheetpath);
		if (!sheet)
		{
			throw std::runtime_error("Spritesheet could not be loaded!");
		}
		Animation animation;
		animation.sheet = std::move(sheet);
		animation.durations = anim_data.durations;
		animation.current_frame = 0;
		animation.current_tick = 0;
		animation.paused = false;
		animation.frames = anim_data.frames;

		return animation;
	}

	AnimationFileData	
	parse_animation_file(std::string filepath)
	{
		std::ifstream in(filepath);
		if (!in)
		{
			throw std::runtime_error("Could not open animation file: " + filepath);
		}
		std::stringstream ss;
		ss << in.rdbuf();
		in.close();
		std::string data(ss.str());

		xml_document<> doc;
		doc.parse<0>(&(data[0])); // parse doesn't like const char * so give it char*
		xml_node<>* anim = doc.first_node();
		std::string sheetpath = anim->first_attribute("spritesheet")->value();
		std::vector<std::string> frame_attrs = { "x", "y", "w", "h" };
		std::vector<SDL_Rect> frame_rects;
		std::vector<SDL_Rect> hitboxes;
		std::vector<SDL_Rect> dmgboxes;
		std::vector<int> durations;
		// Dangerously get attributes without any error checking
		auto get_rect = [](xml_node<> * node) {
			int x = std::stoi(node->first_attribute("x")->value());
			int y = std::stoi(node->first_attribute("y")->value());
			int w = std::stoi(node->first_attribute("w")->value());
			int h = std::stoi(node->first_attribute("h")->value());
			return SDL_Rect{ x, y, w, h };
		};
		for (xml_node<>* frame = anim->first_node(); frame; frame = frame->next_sibling())
		{
			// for right now, let's ignore hitboxes and dmgboxes
			int duration = std::stoi(frame->first_attribute("duration")->value());
			durations.push_back(duration);
			auto rect = get_rect(frame);
			frame_rects.push_back(rect);
		}

		AnimationFileData anim_data;
		anim_data.sheetpath = sheetpath;
		anim_data.frames = frame_rects;
		anim_data.hitboxes = hitboxes;
		anim_data.dmgboxes = dmgboxes;
		anim_data.durations = durations;
		return anim_data;
	}

	static
	void draw_single_frame_animation(SDL_Renderer * renderer, Animation & a, int x, int y)
	{
		SDL_Rect rect;
		rect.x = x;
		rect.y = y;
		// Hacky but just grab first width/height of first frame since frame size is uniform.
		if (a.frames.size() > 0)
		{
			rect.w = a.frames[a.current_frame].w;
			rect.h = a.frames[a.current_frame].h;
		}
		else
		{
			std::cout << "Warning: Animation has no frames.\n";
			rect.w = 0;
			rect.h = 0;
		}

		SDL_RenderCopy(renderer, a.sheet->texture.get(), &(a.frames[a.current_frame]), &rect);
	}

	void play_animation(SDL_Renderer * renderer, Animation & animation, int x, int y, bool reverse)
	{
		if (!animation.paused)
		{
			draw_single_frame_animation(renderer, animation, x, y);
			if (!reverse)
			{
				if (animation.current_tick >= animation.durations[animation.current_frame])
				{
					animation.current_frame++;
					animation.current_tick = 0;
				}
				animation.current_tick++;
				// Restart animation on completion.
				if (animation.current_frame >= animation.frames.size())
				{
					animation.current_frame = 0;
				}
			}
			else
			{
				if (animation.current_tick >= animation.durations[animation.current_frame])
				{
					animation.current_frame--;
					animation.current_tick = 0;
				}
				animation.current_tick++;
				if (animation.current_frame < 0)
				{
					animation.current_frame = animation.frames.size() - 1;
				}
			}
		}
		else
		{
			draw_single_frame_animation(renderer, animation, x, y);
		}
	}

	void switch_animation(Animation & old_anim, Animation & new_anim)
	{
		pause_animation(old_anim);
		unpause_animation(new_anim);
	}

	void pause_animation(Animation & animation)
	{
		animation.paused = true;
	}

	void unpause_animation(Animation & animation)
	{
		animation.paused = false;
	}

	bool is_animation_complete(const Animation & animation)
	{
		size_t frames = animation.frames.size();
		int last_duration = animation.durations.back();
		if (animation.current_frame == frames - 1 && animation.current_tick == last_duration)
			return true;
		return false;
	}

	Animation reverse_animation(const Animation& animation)
	{
		Animation reversed = animation;
		std::reverse(reversed.frames.begin(), reversed.frames.end());
		return reversed;
	}

	void restart_animation(Animation& animation)
	{
		animation.current_frame = 0;
		animation.current_tick = 0;
		animation.paused = false;
	}
}