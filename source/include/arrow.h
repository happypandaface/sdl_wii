#ifndef _ARROW_H_
#define _ARROW_H_

#include "blue_lazer.h"

class Arrow : public BlueLazer 
{
	public:
		Arrow();
		void load_animations(AnimationHolder *animHolder);
};

#endif