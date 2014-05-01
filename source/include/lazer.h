#ifndef _LAZER_H_
#define _LAZER_H_

#include "base_object.h"

class Lazer : public BaseObject
{
	public:
		Lazer();
		virtual int update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		virtual void setDirection(char dir);
		void die(BaseObject *killer);
	private:
		char dir;
};

#endif