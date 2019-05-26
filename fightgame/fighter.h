#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "graphics.h"
#include "movesource.h"

// For now just use an enum for states... eventually 
// extend this behavior... this is all prototype anyway.
enum State
{
	IDLE,
	WALK,
	JUMP,
	DUCK,
	BLOCK,
	MOVE
};

class Fighter
{
public:
	Fighter(bones::GraphicsLoader& loader);

	void read_moves(SDL_Event& event);
	void handle_input(SDL_GameController* controller);
	void tick();
	void draw(SDL_Renderer* renderer);

	void process_move(Move& move);

private:
	MoveSource moveSource;
	int x, y;
	State state;
	void change_state(State to);

	// Animations
	bones::Animation* current_animation;
	bones::Animation idle;
	bones::Animation walk;
};
#endif