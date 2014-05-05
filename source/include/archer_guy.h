#ifndef _ARCHER_GUY_H_
#define _ARCHER_GUY_H_

#include "guy.h"

#define ARROW_GUY_FIRE_COOLDOWN 	1.1
#define ARROW_GUY_FIRE_COOLDOWN_2	1

class ArcherGuy : public Guy
{
	public:
		ArcherGuy();
		int update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		int each_object(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
		void load_animations(AnimationHolder *animHolder);
		void die(BaseObject *killer);
		void setSpawner(BaseObject *spawner);
	private:
		BaseObject *spawner;
		int firingArrow;
		float fireArrowCooldown;
		float fireArrowCount;
};

#endif