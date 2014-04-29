#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "base_object.h"

class Background : public BaseObject
{
	public:
		void load_animations(AnimationHolder *animHolder);
};

#endif