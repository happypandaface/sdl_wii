#include "wall_gun.h"
#include "red_lazer.h"
#include <stdlib.h>

WallGun::WallGun()
{
	size->set(.5, .5);
	fire_rate = 1.4;
}

void WallGun::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_WALL_GUN));
}


int WallGun::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (cooldown <= 0)
	{
		cooldown = fire_rate;
		RedLazer *bl = new RedLazer();
		bl->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		bl->setPos(pos->getX()-.2, pos->getY()+.1);
		bl->setDirection(DIR_LEFT);
		gameProps->addObject(bl);
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}