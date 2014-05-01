#ifndef _WALL_GUN_H_
#define _WALL_GUN_H_

#include "base_object.h"

class WallGun : public BaseObject
{
	public:
		WallGun();
		void load_animations(AnimationHolder *animHolder);
};

#endif