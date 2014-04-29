#ifndef _GIBLET_H_
#define _GIBLET_H_

#include "base_object.h"

class Giblet : public BaseObject
{
	public:
		Giblet();
		void load_animations(AnimationHolder *animHolder);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
	private:
		float timeSinceStart;
};

#endif