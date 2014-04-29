#include "wall.h"

Wall::Wall()
{
	addType(TYP_SOLID);
}

Wall::~Wall()
{
}

void Wall::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_DIRT_BLOCK));
}