#ifndef _BLUE_LAZER_H_
#define _BLUE_LAZER_H_

#include "lazer.h"

class BlueLazer : public Lazer 
{
	public:
		BlueLazer();
		int each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
		void load_animations(AnimationHolder *animHolder);
};

#endif