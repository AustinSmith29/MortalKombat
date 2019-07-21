#include "ai_util.h"

#include <random>

static std::default_random_engine generator;
static std::uniform_real_distribution<double> distribution(0.0, 1.0);

double random()
{
	return distribution(generator);
}