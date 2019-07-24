#include "SDL.h"
#include "graphics.h"
#include "cage.h"
#include "user_fighter.h"
#include "ai_fighter.h"
#include "fighter_animator.h"
#include "collision.h"
#include "easy_ai.h"
#include "dummy_ai.h"
#include "keyboard_device.h"
#include "gamepad_device.h"
#include <iostream>

FighterAnimator create_cage(bones::GraphicsLoader &loader)
{
	auto cage_graphics = load_graphics(loader);
	FighterAnimator cage_animator(cage_graphics);
	return cage_animator;
}

int main(int argc, char *argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screen = NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Mortal Kombat II", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_SHOWN);
	const int FPS = 60;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	bones::GraphicsLoader graphics(renderer);
	bones::Sprite stage = graphics.load_sprite("data/test_stage.bmp");

	FighterAnimator cage_fighter = create_cage(graphics);
	auto move_map = load_moves();
	UserFighter fighter(cage_fighter, &handle_fightmove, move_map);
	fighter.set_position_x(100);
	fighter.set_position_y(400);

	AIFighter opponent(cage_fighter, EasyAI::logic);
	opponent.flip_orientation();
	opponent.set_position_x(300);
	opponent.set_position_y(400);

	int njoysticks = SDL_NumJoysticks();
	std::cout << njoysticks << " detected." << std::endl;
	InputDevice *input_device = new KeyboardDevice();
	//SDL_GameController* controller = SDL_GameControllerOpen(0);
	//InputDevice* input_device = new GamepadDevice(controller);
	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		Uint32 ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			auto input_event = input_device->get_input(event);
			fighter.handle_input_event(input_event, *input_device);
		}

		fighter.tick();
		opponent.tick(fighter);

		fighter.face(opponent.get_position_x());
		opponent.face(fighter.get_position_x());

		handle_fighter_on_fighter_collision(fighter, opponent);
		handle_fighter_on_fighter_collision(opponent, fighter);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		bones::draw_sprite(renderer, stage, 0, 0);
		fighter.draw(renderer);
		opponent.draw(renderer);
		draw_fighter_collision_boxes(renderer, fighter);
		draw_fighter_collision_boxes(renderer, opponent);
		SDL_RenderPresent(renderer);

		int time = SDL_GetTicks() - ticks;
		if (time < (1000 / FPS))
		{
			SDL_Delay((1000 / FPS) - time);
		}
	}
	delete input_device;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}