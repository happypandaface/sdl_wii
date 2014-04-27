#ifndef _GAME_PROPS_H_
#define _GAME_PROPS_H_

#include "pos2.h"

class GameProperties
{
	public:
		GameProperties();
		~GameProperties();
		Pos2 *getOffset();
		Pos2 *addOffset(float x, float y);
		Pos2 *getTileSize();
		Pos2 *setTileSize(float x, float y);
	private:
		Pos2 *offset;
		Pos2 *tileSize;
};

#endif