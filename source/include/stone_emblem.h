#ifndef _STONE_EMBLEM_H_
#define _STONE_EMBLEM_H_

#include "base_object.h"
#include "spawner.h"

class StoneEmblem : public Spawner, public BaseObject
{
	public:
		StoneEmblem();
		void load_animations(AnimationHolder *animHolder);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		Pos2 *getSpawnPos();
		void setActive();
		void setInactive();
	private:
		int active;
		int changedFireAnim;
};

#endif