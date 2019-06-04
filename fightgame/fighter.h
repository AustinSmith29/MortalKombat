#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "graphics.h"
#include "movesource.h"
#include "fighter_state.h"

class Fighter
{
public:

	Fighter();
	Fighter(Fighter& rhs) = delete;
	Fighter(Fighter&& rhs) = delete;

	void handle_input_event(SDL_Event& event);
	void handle_input_state(SDL_GameController* controller);

	virtual void load_resources(bones::GraphicsLoader& loader) = 0;
	virtual void process_move(Move& move) = 0;

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	FighterState get_state();
	void flip_orientation();
	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	bool airborne;
	FighterState state;
	MoveSource move_source;

	bones::Animation* current_animation;
	bones::Animation idle;
	bones::Animation crouch;
	bones::Animation jump;
	bones::Animation jump_move_forward;
	bones::Animation jump_move_backward;
	bones::Animation walk_forward;
	bones::Animation walk_backward;

private:
	void idle_state(FighterState::Action action);
	void crouch_state(FighterState::Action action);
	void jump_state(FighterState::Action action);
	void thrown_state(FighterState::Action action);
	void knocked_state(FighterState::Action action);
};
#endif