#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace bones 
{
	struct Sprite
	{
		Sprite() = delete;
		Sprite(std::shared_ptr<SDL_Texture> texture) { this->texture = texture; }

		std::shared_ptr<SDL_Texture> texture; 
	};

	struct Animation
	{
		std::shared_ptr<Sprite> sheet;       /// spritesheet the animation utilizes
		std::vector<SDL_Rect> frames;        /// clippings on sprite sheet of frames
		std::vector<int> durations;			 /// how many frames each frame should play
		std::map<int, std::vector<SDL_Rect>> hitboxes; /// hitboxes for each frame
		std::map<int, std::vector<SDL_Rect>> dmgboxes; /// damageboxes for each frame
		int current_frame;					 /// current_frame of the animation
		unsigned int current_tick;			 /// current tick of current frame
		bool paused;                         /// determines if we play animation
		SDL_RendererFlip flip{SDL_FLIP_NONE};			 /// what type of flip type
	};

	class GraphicsLoader
	{
	public:
		GraphicsLoader() = delete;
		GraphicsLoader(SDL_Renderer* renderer);

		Sprite load_sprite(std::string filepath);
		Animation load_animation(std::string filepath);

	private:
		std::map<std::string, std::shared_ptr<SDL_Texture>> registry;
		SDL_Renderer* renderer;

		bool is_texture_in_registry(std::string filepath);
		std::shared_ptr<SDL_Texture> get_loaded_texture(std::string filepath);
		std::shared_ptr<SDL_Texture> load_new_texture(std::string filepath);
	};

	void draw_sprite(SDL_Renderer* renderer, Sprite& sprite, int x, int y);

	void play_animation(SDL_Renderer* renderer, Animation& animation, int x, int y, bool reverse = false);

	void switch_animation(Animation& old_anim, Animation& new_anim);
	void pause_animation(Animation& animation);
	void unpause_animation(Animation& animation);

	bool is_animation_complete(const Animation& animation);
	Animation reverse_animation(const Animation& animation);
	void restart_animation(Animation& animation);
	void flip_animation(Animation& animation);
}
#endif