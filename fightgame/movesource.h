#ifndef _MOVESOURCE_H
#define _MOVESOURCE_H

#include "graphics.h"
#include "fighter_state.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1

struct Move
{
	bones::Animation animation;
	std::string name;
	int damage;
};

class Fighter;
class MoveSource
{
public:
	MoveSource();
	MoveSource(Fighter *owner);
	~MoveSource();

	void bind_owner(Fighter* owner);
	void bind_move(FighterState::State state, std::string input_seq, Move move);
	void load_moves_from_file(std::string filename, bones::GraphicsLoader &loader);
	void process_event(SDL_Event &event, int direction);
	void flush();

private:
	std::vector<std::string> input_buffer;
	std::map<std::pair<FighterState::State, std::string>, Move> move_map;
	bool first_press; /// start flush timer once this is true
	Fighter* owner;
};
#endif