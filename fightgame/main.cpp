#include "SDL.h"
#include "graphics.h"
#include "cage.h"
#include "constants.h"
#include "user_fighter.h"
#include "ai_fighter.h"
#include "fighter_animator.h"
#include "collision.h"
#include "easy_ai.h"
#include "dummy_ai.h"
#include "keyboard_device.h"
#include "gamepad_device.h"
#include "projectile_factory.h"
#include <iostream>

FighterAnimator create_cage(bones::GraphicsLoader &loader)
{
	auto cage_graphics = load_graphics(loader);
	FighterAnimator cage_animator(cage_graphics);
	return cage_animator;
}

void focus_camera(SDL_Rect& camera, Fighter& a, Fighter& b);
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
	SDL_RenderSetLogicalSize(renderer, 400, 254);
	bones::GraphicsLoader graphics(renderer);
	bones::Sprite stage = graphics.load_sprite("data/test_stage.bmp");

	SDL_Rect camera = { 100, 150, 400, 254 };

	FighterAnimator cage_fighter = create_cage(graphics);
	auto move_map = load_moves();
	UserFighter fighter(cage_fighter, move_map);
	fighter.set_position_x(200);
	fighter.set_position_y(400);

	AIFighter opponent(cage_fighter, DummyAI::logic);
	opponent.flip_orientation();
	opponent.set_position_x(400);
	opponent.set_position_y(400);

	ProjectileFactory::load(graphics);

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

		focus_camera(camera, fighter, opponent);
		fighter.tick();
		opponent.tick(fighter);

		face(fighter, opponent.get_position_x());
		face(opponent, fighter.get_position_x());

		handle_fighter_on_fighter_collision(fighter, opponent);
		auto fighter_projectiles = fighter.get_projectiles();
		auto opponent_projectiles = opponent.get_projectiles();
		for (auto& projectile : *fighter_projectiles)
		{
			handle_fighter_on_projectile_collision(opponent, *projectile);
		}
		for (auto& projectile : *opponent_projectiles)
		{
			handle_fighter_on_projectile_collision(fighter, *projectile);
		}
		handle_fighter_on_fighter_collision(opponent, fighter);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		bones::draw_sprite(renderer, stage, -camera.x, -camera.y);
		fighter.draw(renderer, camera);
		opponent.draw(renderer, camera);
		//draw_fighter_collision_boxes(renderer, fighter);
		//draw_fighter_collision_boxes(renderer, opponent);
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

void focus_camera(SDL_Rect& camera, Fighter& a, Fighter& b)
{
	const int CAMERA_PAD = 64;
	int a_x = a.get_position_x();
	int b_x = b.get_position_x();
	int dx = a_x - b_x;

	if (a_x + CAMERA_PAD > camera.x + camera.w ||
		b_x + CAMERA_PAD > camera.x + camera.w)
	{
		camera.x += 2;
	}

	if (a_x - CAMERA_PAD < camera.x  ||
		b_x - CAMERA_PAD < camera.x)
	{
		camera.x -= 2;
	}
	// don't let fighter move out of camera sight
	if (dx > camera.w - CAMERA_PAD-20) 
		a.set_position_x(camera.x + camera.w - 20);
	if (-dx > camera.w - CAMERA_PAD - 20)
		b.set_position_x(camera.x + camera.w - 20);

	if (a.get_position_x() < camera.x + CAMERA_PAD)
		a.set_position_x(camera.x + CAMERA_PAD);
	if (b.get_position_x() < camera.x + CAMERA_PAD)
		b.set_position_x(camera.x + CAMERA_PAD);

	// TODO: ADD CAMERA LIMITS
	if (camera.x < 0)
		camera.x = 0;
	if (camera.x + camera.w > MAP_WIDTH)
		camera.x = MAP_WIDTH - camera.w;

}