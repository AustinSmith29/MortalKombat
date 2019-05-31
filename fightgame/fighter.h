#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "graphics.h"
#include "movesource.h"
#include "fighter_state.h"

#include <vector>

class Fighter
{
public:

	virtual void load_resources(bones::GraphicsLoader& loader) {}
	virtual void handle_input_event(SDL_Event& event) {}
	virtual void handle_input_state(SDL_GameController* controller) {}
	virtual void process_move(Move& move) {}

	FighterState get_state();
	void hit();
	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int health;
	FighterState state;
	bones::Animation* current_animation;
	MoveSource move_source;

private:
	virtual void idle_state(FighterState::Action action) {}
	virtual void crouch_state(FighterState::Action action) {}
	virtual void jump_state(FighterState::Action action) {}
	virtual void thrown_state(FighterState::Action action) {}
	virtual void knocked_state(FighterState::Action action) {} 
};
#endif