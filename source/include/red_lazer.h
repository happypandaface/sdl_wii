#ifndef _RED_LAZER_H_
#define _RED_LAZER_H_

#include "lazer.h"

class RedLazer : public Lazer
{
	public:
		RedLazer();
		void load_animations(AnimationHolder *animHolder);
		int each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
};

#endif