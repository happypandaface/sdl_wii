#ifndef _ARCHER_GUY_SPAWN_H_
#define _ARCHER_GUY_SPAWN_H_

#include "base_object.h"

class ArcherGuySpawn : public BaseObject
{
	public:
		ArcherGuySpawn();
		int update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		void alertDeath(BaseObject *died);
	private:
		BaseObject *spawned;
};

#endif