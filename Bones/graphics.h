/** @file Graphics.h
 *  @brief Definitions used to handle graphics.
 *
 *  This contains the objects that will be used to draw sprites and animations
 *  to the screen.
 *
 *  @author Austin Smith
 *  @bug No known bugs.
 **/

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <SDL.h>
#include <memory>
#include <string>
#include <vector>
#include <map>

namespace bones 
{
	/**
	 * Sprite
	 * A _Sprite wraps the functionality of a SDL_Texture. They are the
	 * images that can be drawn on the screen.
	 **/
	struct Sprite
	{
		Sprite() = default;
		Sprite(std::shared_ptr<SDL_Texture> texture) { this->texture = texture; }

		std::shared_ptr<SDL_Texture> texture;  /// texture resource this sprite uses
	};

	/**
	 * Animation
	 * An Animation is exactly what it sounds like. It stores
	 * information that allows sprites to be animated.
	 **/
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
	};

	/**
	 * GraphicsLoader
	 * GraphicsLoader loads and returns created Sprite and Animation objects while
	 * keeping track of SDL_Textures' that have already been loaded so the same
	 * resource does not get loaded into memory more than once.
	 **/
	class GraphicsLoader
	{
	public:
		/**
		 * Register this service with the renderer so that it can be used.
		 * GraphicsLoader instances can not be used without first registering.
		 * @param renderer the SDL_Renderer this GraphicsLoader will use.
		 **/
		void register_service(SDL_Renderer* renderer);

		/**
		 * Loads an image and returns a created Sprite.
		 * @param filepath the filepath to the image file
		 * @return the created Sprite
		 **/
		std::unique_ptr<Sprite> load_sprite(std::string filepath);

		/**
		 * Loads an image and returns a created Animation.
		 * @param filepath the filepath to the animation datafile.
		 * @return the created Animation.
		 **/
		Animation load_animation(std::string filepath);

	private:
		std::map<std::string, std::shared_ptr<SDL_Texture>> registry;
		SDL_Renderer* renderer;
	};

	void draw_sprite(SDL_Renderer* renderer, Sprite& sprite, int x, int y);

	void play_animation(SDL_Renderer* renderer, Animation& animation, int x, int y, bool reverse = false);

	/**
	 * Pauses old animation and unpauses new_anim.
	 **/
	void switch_animation(Animation& old_anim, Animation& new_anim);
	void pause_animation(Animation& animation);
	void unpause_animation(Animation& animation);

	bool is_animation_complete(const Animation& animation);
	Animation reverse_animation(const Animation& animation);
	void restart_animation(Animation& animation);
}
#endif