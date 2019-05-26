#ifndef _MOVESOURCE_H
#define _MOVESOURCE_H

#include "graphics.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1

class Fighter;
struct Move
{
	bones::Animation animation;
	std::string name;
	int damage;
};

class MoveSource
{
public:
	MoveSource(Fighter *owner);
	~MoveSource();

	void bind_move(std::string key, Move move);
	void load_moves_from_file(std::string filename, bones::GraphicsLoader &loader);
	void process_event(SDL_Event &event, int direction);
	void flush();

private:
	std::vector<std::string> input_buffer;
	std::map<std::string, Move> move_map;
	bool first_press; /// start flush timer once this is true
	Fighter* owner;
};
#endif