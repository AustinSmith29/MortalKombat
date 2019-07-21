#include "SDL.h"
#include "graphics.h"
#include "cage.h"
#include "user_fighter.h"
#include "ai_fighter.h"
#include "fighter_animator.h"
#include "collision.h"
#include "easy_ai.h"
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

	FighterAnimator cage_fighter = create_cage(graphics);
	auto move_map = load_moves();
	UserFighter fighter(cage_fighter, &handle_fightmove, move_map);
	fighter.set_position_x(100);
	fighter.set_position_y(350);
	Collider collider(fighter);

	AIFighter opponent(cage_fighter, EasyAI::logic);
	opponent.flip_orientation();
	opponent.set_position_x(300);
	opponent.set_position_y(350);
	Collider collider2(opponent);

	int njoysticks = SDL_NumJoysticks();
	std::cout << njoysticks << " detected." << std::endl;
	SDL_GameController* controller = SDL_GameControllerOpen(0);
	SDL_Event event;
	bool quit = false;
	SDL_Rect test = { 200, 250, 64, 100 };
	while (!quit)
	{
		Uint32 ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			fighter.handle_input_event(event, controller);
		}

		fighter.tick();
		opponent.tick(fighter);

		fighter.face(opponent.get_position_x());
		opponent.face(fighter.get_position_x());

		if (collider2.damagebox_collision(collider))
		{
			std::cout << "Ouch!\n";
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		fighter.draw(renderer);
		opponent.draw(renderer);
		collider.draw_boxes(renderer);
		collider2.draw_boxes(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, &test);
		SDL_RenderPresent(renderer);

		int time = SDL_GetTicks() - ticks;
		if (time < (1000 / FPS))
		{
			SDL_Delay((1000 / FPS) - time);
		}
	}
	SDL_GameControllerClose(controller);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}