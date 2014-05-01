#include "wall.h"

struct Neighbor
{
	int exists;
};

Wall::Wall()
{
	neighbors = new struct Neighbor[NUM_NEIGHBORS];
	addType(TYP_SOLID);
}

Wall::~Wall()
{
}

void Wall::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_DIRT_BLOCK));
	wallNorth = new AnimationInstance(animHolder->get_anim(ANIM_DIRT_WALL_N));
	wallEast = new AnimationInstance(animHolder->get_anim(ANIM_DIRT_WALL_E));
	wallSouth = new AnimationInstance(animHolder->get_anim(ANIM_DIRT_WALL_S));
	wallWest = new AnimationInstance(animHolder->get_anim(ANIM_DIRT_WALL_W));
}
int Wall::doDraw(float x, float y, ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen)
{
	animInst->draw(
		resLoader, 
		screen, 
		x, 
		y
	);
	if (neighbors[NEIGHBOR_EAST].exists == 1)
		wallEast->draw(
			resLoader, 
			screen, 
			x, 
			y
		);
	if (neighbors[NEIGHBOR_WEST].exists == 1)
		wallWest->draw(
			resLoader, 
			screen, 
			x, 
			y
		);
	if (neighbors[NEIGHBOR_NORTH].exists == 1)
		wallNorth->draw(
			resLoader, 
			screen, 
			x, 
			y
		);
	if (neighbors[NEIGHBOR_SOUTH].exists == 1)
		wallSouth->draw(
			resLoader, 
			screen, 
			x, 
			y
		);
	return 1;
}

void Wall::calcNeighbors(ObjectHolder *objHolder, GameProperties *gameProps)
{
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		Wall *wll = dynamic_cast<Wall*>(curr);
		if (wll != NULL)
		{
			if (curr->getPosition()->getX() == getPosition()->getX())
			{
				if (curr->getPosition()->getY() == getPosition()->getY()+getSize()->getY())
				{
					canShoves &= ~DIR_DOWN;
					neighbors[NEIGHBOR_SOUTH].exists = 1;
				}else
				if (curr->getPosition()->getY() == getPosition()->getY()-getSize()->getY())
				{
					canShoves &= ~DIR_UP;
					neighbors[NEIGHBOR_NORTH].exists = 1;
				}
			}else
			if (curr->getPosition()->getY() == getPosition()->getY())
			{
				if (curr->getPosition()->getX() == getPosition()->getX()+getSize()->getX())
				{
					canShoves &= ~DIR_RIGHT;
					neighbors[NEIGHBOR_EAST].exists = 1;
				}else
				if (curr->getPosition()->getX() == getPosition()->getX()-getSize()->getX())
				{
					canShoves &= ~DIR_LEFT;
					neighbors[NEIGHBOR_WEST].exists = 1;
				}
			}
		}
	}
	objHolder->destroyIterator(objIter);
}
int Wall::hasNeighbor(int neighbor)
{
	return 0;
}