#ifndef _FIGHTMOVE_INPUT_HANDLER_H
#define _FIGHTMOVE_INPUT_HANDLER_H

#include "fighter_state.h"
#include "fightmove.h"
#include "input_device.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

class FightMoveInputHandler
{
public:
	using HandlerFunc = std::function<void(FightMove, Fighter&)>;
	using ActivationKey = std::pair<FightMoveHook, std::string>;

	FightMoveInputHandler(HandlerFunc handler, std::map<ActivationKey, FightMove> move_map);
	FightMoveInputHandler(const FightMoveInputHandler& handler) = delete;
	FightMoveInputHandler& operator = (const FightMoveInputHandler& handler) = delete;

	void process_event(InputEvent &event, FightMoveHook hook, Orientation direction, Fighter &fighter);
	void flush();

	static ActivationKey make_key(FightMoveHook hook, std::string input);

private:
	std::vector<std::string> input_buffer;
	std::map<ActivationKey, FightMove> move_map;
	HandlerFunc handler;
	bool first_press; /// start flush timer once this is true
};
#endif