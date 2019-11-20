#include "gamestate.h"
#include "fighter.h"
#include "user_fighter.h"
#include "ai_fighter.h"
#include "collision.h"
#include "constants.h"
#include "projectile_factory.h" // Do we need this file/class?

void focus_camera(SDL_Rect& camera, Fighter& a, Fighter& b);
std::unique_ptr<Fighter> create_ai_fighter(int type, bones::GraphicsLoader& loader);
std::unique_ptr<Fighter> create_user_fighter(int type, bones::GraphicsLoader& loader);

void GameState::init(int type_a, bool ai_a, int type_b, bool ai_b,
	bones::GraphicsLoader& loader, InputDevice* device1,
	InputDevice* device2)
{
	ProjectileFactory::load(loader);
	fighter_a = (ai_a) ? create_ai_fighter(type_a, loader) :
		create_user_fighter(type_a, loader);

	fighter_b = (ai_b) ? create_ai_fighter(type_b, loader) :
		create_user_fighter(type_b, loader);

	fighter_a_ai = ai_a;
	fighter_b_ai = ai_b;

	stage = loader.load_sprite("data/test_stage.bmp");

	camera = SDL_Rect{ 100, 150, 400, 254 };
	input_devices[0] = device1;
	input_devices[1] = device2;

	fighter_a->set_position_x(20);
	fighter_a->set_position_y(400);
	fighter_b->flip_orientation();
	fighter_b->set_position_x(400);
	fighter_b->set_position_y(400);
}

void GameState::handle_input(SDL_Event& event)
{
	if (!fighter_a_ai)
	{
		auto fighter_a_input = input_devices[0]->get_input(event);
		static_cast<UserFighter*>(fighter_a.get())->handle_input_event(fighter_a_input, *input_devices[0]);
	}
	if (!fighter_b_ai)
	{
		auto fighter_b_input = input_devices[1]->get_input(event);
		static_cast<UserFighter*>(fighter_b.get())->handle_input_event(fighter_b_input, *input_devices[1]);
	}
}

void GameState::tick()
{
	focus_camera(camera, *fighter_a, *fighter_b);
	if (!fighter_a_ai)
		static_cast<UserFighter*>(fighter_a.get())->tick();
	else
		static_cast<AIFighter*>(fighter_a.get())->tick(*fighter_b);

	if (!fighter_b_ai)
		static_cast<UserFighter*>(fighter_b.get())->tick();
	else
		static_cast<AIFighter*>(fighter_b.get())->tick(*fighter_a);

	face(*fighter_a, fighter_b->get_position_x());
	face(*fighter_b, fighter_a->get_position_x());
	handle_fighter_on_fighter_collision(*fighter_a, *fighter_b);
	handle_fighter_on_fighter_collision(*fighter_b, *fighter_a);

	for (auto& projectile : *fighter_a->get_projectiles())
		handle_fighter_on_projectile_collision(*fighter_b, *projectile);
	for (auto& projectile : *fighter_b->get_projectiles())
		handle_fighter_on_projectile_collision(*fighter_a, *projectile);
}

void draw_health(int health, int x, int y, SDL_Renderer* renderer)
{
	SDL_Rect background = { x, y, 100, 16 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &background);
	SDL_Rect bar = { x, y, health, 16 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &bar);
}

void GameState::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	bones::draw_sprite(renderer, stage, -camera.x, -camera.y);
	draw_health(fighter_a->get_health(), 20, 20, renderer);
	draw_health(fighter_b->get_health(), 280, 20, renderer);
	fighter_a->draw(renderer, camera);
	fighter_b->draw(renderer, camera);
}

void focus_camera(SDL_Rect& camera, Fighter& a, Fighter& b)
{
	const int CAMERA_PAD = 64;
	int a_x = a.get_position_x();
	int b_x = b.get_position_x();
	int dx = a_x - b_x;

	// Camera Scroll
	if (a_x + CAMERA_PAD > camera.x + camera.w ||
		b_x + CAMERA_PAD > camera.x + camera.w)
	{
		camera.x += 2;
	}

	if (a_x - CAMERA_PAD < camera.x ||
		b_x - CAMERA_PAD < camera.x)
	{
		camera.x -= 2;
	}
	// don't let fighter move out of camera sight
	if (dx > camera.w - CAMERA_PAD - 20)
		a.set_position_x(camera.x + camera.w - 20);
	if (-dx > camera.w - CAMERA_PAD - 20)
		b.set_position_x(camera.x + camera.w - 20);

	if (a.get_position_x() < camera.x + CAMERA_PAD)
		a.set_position_x(camera.x + CAMERA_PAD);
	if (b.get_position_x() < camera.x + CAMERA_PAD)
		b.set_position_x(camera.x + CAMERA_PAD);

	// CAMERA LIMITS
	if (camera.x < 0)
		camera.x = 0;
	if (camera.x + camera.w > MAP_WIDTH)
		camera.x = MAP_WIDTH - camera.w;

}

// temporarily uses load_graphics function in cage.cpp file
#include "cage.h"
#include "dummy_ai.h"
std::unique_ptr<Fighter> create_ai_fighter(int type, bones::GraphicsLoader& loader)
{
	auto graphics = load_graphics(loader);
	FighterAnimator cage_animator(graphics);
	return std::make_unique<AIFighter>(cage_animator, DummyAI::logic);
}
std::unique_ptr<Fighter> create_user_fighter(int type, bones::GraphicsLoader& loader)
{
	auto graphics = load_graphics(loader);
	FighterAnimator cage_animator(graphics);
	auto move_map = load_moves();
	return std::make_unique<UserFighter>(cage_animator, move_map);
}
