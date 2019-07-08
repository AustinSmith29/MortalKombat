#ifndef _MOVESOURCE_H
#define _MOVESOURCE_H

#include "graphics.h"
#include "fighter_state.h"
#include "fighter_animator.h"
#include "fightmove.h"

#include <string>
#include <vector>
#include <map>

class Fighter;
class FightMoveInputHandler
{
public:
	FightMoveInputHandler(Fighter &owner);

	void bind_move(FighterState::FightMoveHook state, std::string input_seq, FightMove move);
	void load_moves_from_file(std::string filename, bones::GraphicsLoader &loader);
	void process_event(SDL_Event &event, Orientation direction);
	void flush();

private:
	std::vector<std::string> input_buffer;
	std::map<std::pair<FighterState::FightMoveHook, std::string>, FightMove> move_map;
	bool first_press; /// start flush timer once this is true
	Fighter& owner;
};
#endif