#include "archer_guy_spawn.h"
#include "archer_guy.h"

ArcherGuySpawn::ArcherGuySpawn()
{
	spawned = NULL;
}

int ArcherGuySpawn::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (spawned == NULL)
	{
		ArcherGuy *aGuy = new ArcherGuy();
		aGuy->setSpawner(this);
		aGuy->setDirection(DIR_LEFT);
		aGuy->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		aGuy->setPos(getPosition()->getX(), getPosition()->getY());
		spawned = aGuy;
		gameProps->addObject(aGuy);
	}
	return 0;
}

void ArcherGuySpawn::alertDeath(BaseObject *died)
{
	spawned = NULL;
}