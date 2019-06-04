#ifndef _CAGE_H
#define _CAGE_H

#include "fighter.h"

class JohnnyCage : public Fighter
{
public:
	void load_resources(bones::GraphicsLoader& loader) override;
	void process_move(Move& move) override;
};
#endif