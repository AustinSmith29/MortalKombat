#ifndef _CAGE_H
#define _CAGE_H

#include "fighter.h"

class JohnnyCage : public Fighter
{
public:
	void load_resources(bones::GraphicsLoader& loader) override;
	void handle_input_event(SDL_Event& event) override;
	void handle_input_state(SDL_GameController* controller) override;
	void process_move(Move& move) override;
private:
	int x_vel, y_vel;
	bool airborne;
	bones::Animation idle;
	bones::Animation crouch;
	bones::Animation jump;
	bones::Animation jump_move_forward;
	bones::Animation jump_move_backward;
	bones::Animation walk_forward;
	bones::Animation walk_backward;

	void idle_state(FighterState::Action action) override;
	void crouch_state(FighterState::Action action) override;
	void jump_state(FighterState::Action action) override;
	void thrown_state(FighterState::Action action) override;
	void knocked_state(FighterState::Action action) override;
};
#endif