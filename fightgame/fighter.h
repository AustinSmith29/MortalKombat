#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "graphics.h"
#include "movesource.h"
#include "all_fight_states.h"

enum class FighterGraphics
{
	IDLE,
	CROUCH,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD,
	WALK_FORWARD,
	WALK_BACKWARD,
	BLOCK_STAND,
	BLOCK_CROUCH,
	FIGHT_MOVE
};

class Fighter
{
public:

	Fighter();
	Fighter(Fighter& rhs) = delete;
	Fighter(Fighter&& rhs) = delete;

	void handle_input_event(SDL_Event& event);
	void handle_input_state(SDL_GameController* controller);

	virtual void load_resources(bones::GraphicsLoader& loader) = 0;
	virtual void process_move(Move& move);

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	Orientation get_orientation();
	FighterState::FightMoveHook get_fight_move_hook();
	void move_right();
	void move_left();
	void set_graphics(FighterGraphics graphics);
	void flip_orientation();
	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	MoveSource move_source;
	bones::Animation* current_animation;

private:
	void handle_button_press(Uint8 button);
	void handle_button_release(Uint8 button);
	void change_state_if_open(FighterState *to);
	void set_state(FighterState* to);
	Orientation orientation;
	FighterState* current_state;
	IdleState idle_state;
	CrouchState crouch_state;
	MoveRightState move_right_state;
	MoveLeftState move_left_state;
	FightMoveState fightmove_state;
};
#endif