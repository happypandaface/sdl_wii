#ifndef _WALL_H_
#define _WALL_H_

#include "base_object.h"

class Wall : public BaseObject
{
	public:
		Wall();
		~Wall();
		void load_animations(AnimationHolder *animHolder);
};
#endif