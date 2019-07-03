#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "fighter_animator.h"
#include "movesource.h"
#include "all_fight_states.h"

class Fighter
{
public:

	Fighter();
	Fighter(Fighter& rhs) = delete;
	Fighter(Fighter&& rhs) = delete;

	void handle_input_event(SDL_Event& event, SDL_GameController *controller);
	void handle_input_state(SDL_GameController* controller);

	virtual void load_resources(bones::GraphicsLoader& loader) = 0;
	virtual void process_move(Move& move) = 0;

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	Orientation get_orientation();
	FighterState::FightMoveHook get_fight_move_hook();
	bones::Animation* get_animation();
	void move_right(); // TODO: redundant???
	void move_left();  // TODO: redundant???

	int get_velocity_y();
	void set_velocity_y(int val);

	int get_position_y();
	void set_position_y(int val);

	void perform_fight_move(bones::Animation& move);
	void set_graphics(FighterGraphics graphics);
	void flip_orientation();
	void reset_state();

	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	MoveSource move_source;
	FighterAnimator animator;

private:
	void handle_button_press(Uint8 button, SDL_GameController *controller);
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
	JumpState jump_state;
	JumpRightState jump_right_state;
	JumpLeftState jump_left_state;
	BlockState block_state;
};
#endif