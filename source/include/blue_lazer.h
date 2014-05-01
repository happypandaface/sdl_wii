#ifndef _BLUE_LAZER_H_
#define _BLUE_LAZER_H_

#include "lazer.h"

class BlueLazer : public Lazer 
{
	public:
		BlueLazer();
		void load_animations(AnimationHolder *animHolder);
};

#endif