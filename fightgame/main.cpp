#include "SDL.h"
#include "graphics.h"
#include "movesource.h"
#include "cage.h"
#include "collision.h"
#include <iostream>

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
	int njoysticks = SDL_NumJoysticks();
	std::cout << njoysticks << " detected." << std::endl;
	SDL_GameController* controller = SDL_GameControllerOpen(0);
	graphics.register_service(renderer);
	Fighter *fighter;
	JohnnyCage cage;
	fighter = &cage;
	Collider collider(fighter);
	fighter->load_resources(graphics);
	SDL_Event event;
	bool quit = false;
	SDL_Rect test = { 200, 250, 64, 100 };
	while (!quit)
	{
		Uint32 ticks = SDL_GetTicks();
		Move move;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			fighter->handle_input_event(event);
		}
		fighter->handle_input_state(controller);
		fighter->tick();
		if (collider.damagebox_collision(test))
		{
			std::cout << "Hit!" << std::endl;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		fighter->draw(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(renderer, &test);
		collider.draw_boxes(renderer);
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