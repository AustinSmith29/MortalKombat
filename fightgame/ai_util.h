#ifndef _AI_UTIL_H
#define _AI_UTIL_H

#include <stdexcept>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

double random();

class Fighter;
unsigned int x_distance(Fighter& a, Fighter& b);

namespace Behavior
{
	using BehaviorFunc = std::function<void(Fighter&, Fighter&)>;
	void jump_towards(Fighter& subject, Fighter& target);
	void jump_away(Fighter& subject, Fighter& target);
	void move_towards(Fighter& subject, Fighter& target);
	void move_away(Fighter& subject, Fighter& target);
	void idle(Fighter& subject, Fighter& target);
};

template <typename T, typename V>
bool pair_compare(const std::pair<T, V>& a, const std::pair<T, V>& b)
{
	return (a.first < b.first);
}

template <typename T> 
T nonuni_random_state_from(std::vector<std::pair<int, T>> prob_map)
{
	int prob_total = 0;
	int last_prob = 0;
	for (auto& item : prob_map) {
		prob_total += item.first;
		last_prob += item.first;
		item.first += last_prob;
	}
	if (prob_total != 100)
		throw std::logic_error("Probabilities must sum to 1.");
	
	int roll = static_cast<int>(random() * 100);
	for (auto item : prob_map)
	{
		if (roll < item.first)
			return item.second;
	}
	return prob_map[0].second;
}
#endif