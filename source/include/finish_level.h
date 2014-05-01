#ifndef _FINISH_LEVEL_H_
#define _FINISH_LEVEL_H_

#include "base_object.h"

class FinishLevel : public BaseObject
{
	public:
		FinishLevel();
		void load_animations(AnimationHolder *animHolder);
		int each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
	private:
		float ending_level_time;
		int ending_level;
};
#endif