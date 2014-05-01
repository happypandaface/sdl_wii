#ifndef _WALL_H_
#define _WALL_H_

#include "base_object.h"
#include "game_properties.h"
#include "object_holder.h"

#define NUM_NEIGHBORS 4

struct Neighbor;

#define NEIGHBOR_NORTH 1
#define NEIGHBOR_SOUTH 2
#define NEIGHBOR_EAST 3
#define NEIGHBOR_WEST 4

class Wall : public BaseObject
{
	public:
		Wall();
		~Wall();
		void load_animations(AnimationHolder *animHolder);
		virtual void calcNeighbors(ObjectHolder *objHolder, GameProperties *gameProps);
		int doDraw(float x, float y, ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen);
	protected:
		virtual int hasNeighbor(int neighbor);
		struct Neighbor *neighbors;
		AnimationInstance *wallNorth;
		AnimationInstance *wallEast;
		AnimationInstance *wallSouth;
		AnimationInstance *wallWest;
};
#endif