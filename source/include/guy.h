#ifndef _GUY_H_
#define _GUY_H_

#include "base_object.h"

class Guy : public BaseObject
{
	public:
		Guy();
		void die(BaseObject *killer);
		void doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		int checkDeath(GameProperties *gameProps);
};

#endif