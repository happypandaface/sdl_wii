#ifndef _SPIKE_BALL_H_
#define _SPIKE_BALL_H_

#include "patroller.h"

class SpikeBall : public Patroller
{
	public:
		void load_animations(AnimationHolder *animHolder);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
};

#endif