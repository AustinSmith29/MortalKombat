#ifndef _FIGHTER_STATE
#define _FIGHTER_STATE

#include <SDL.h>

class Fighter;
class FighterState
{
public:
	virtual void enter(Fighter &fighter) = 0;
	virtual void tick(Fighter &fighter) = 0;
	virtual void exit(Fighter &fighter) = 0;
};
#endif