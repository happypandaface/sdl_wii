#include "lazer.h"

Lazer::Lazer()
{
	dir = 0;
	addType(TYP_HITS);
	restitution = 0;
	size->set(.5, .25);
}

void Lazer::setDirection(char dir)
{
	if (dir & DIR_LEFT)
		vel->setX(-speed);
	else if (dir & DIR_RIGHT)
		vel->setX(speed);
	BaseObject::setDirection(dir);
}

void Lazer::setShooter(BaseObject *b)
{
	shooter = b;
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

int Lazer::each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	if (curr->checkType(TYP_SOLID))
	{
		Pos2 *dst = pos->intersection(
			size, 
			curr->getPosition(), 
			curr->getSize());
		if (dst)
		{
			die(this);
			delete dst;
		}
	}
	return 1;
}