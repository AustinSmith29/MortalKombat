#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "graphics.h"
#include "input_device.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <array>

class Fighter;
class GameState
{
public:
	void init(int fighter_a, bool ai_a, int fighter_b, bool ai_b,
		bones::GraphicsLoader& loader,
		InputDevice* device1,
		InputDevice* device2);
	void handle_input(SDL_Event& event);
	void tick();
	void render(SDL_Renderer *renderer);
private:
	std::unique_ptr<Fighter> fighter_a;
	std::unique_ptr<Fighter> fighter_b;
	std::array<InputDevice*, 2> input_devices;
	bool fighter_a_ai, fighter_b_ai;
	bones::Sprite stage;
	SDL_Rect camera;
	int time;
	int round;
	TTF_Font* font;
	SDL_Texture* timer;
	void draw_timer(SDL_Renderer* renderer);
};

#endif