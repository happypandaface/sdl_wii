#include "lazer.h"

Lazer::Lazer()
{
	dir = 0;
	addType(TYP_HITS);
	restitution = 0;
}

void Lazer::setDirection(char dir)
{
	if (dir & DIR_LEFT)
		vel->setX(-speed);
	else if (dir & DIR_RIGHT)
		vel->setX(speed);
}

int Lazer::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (timeSinceStart > .5)
		addType(TYP_DEAD);
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}

void Lazer::die(BaseObject *killer)
{
	addType(TYP_DEAD);
}