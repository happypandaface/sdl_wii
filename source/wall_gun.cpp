#include "wall_gun.h"
#include <stdlib.h>

WallGun::WallGun()
{
	size->set(.5, .5);
}

void WallGun::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_WALL_GUN));
}