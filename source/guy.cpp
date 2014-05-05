#include "player.h"
#include "res_loader.h"
#include "animation_holder.h"
#include "giblet.h"
#include "player_indicator.h"
#include "blue_lazer.h"

Guy::Guy()
{
	addType(TYP_CLIPS);
	addType(TYP_HAS_GRAV);
	setLayer(1);
	dir_facing = DIR_RIGHT;// so that we have an initial direction
}

void Guy::die(BaseObject *killer)
{
	addType(TYP_DEAD);
}

void Guy::doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	// add the giblets!
	for (int i = 0; i < 5; ++i)
	{
		Giblet *g1 = new Giblet();
		g1->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		g1->setPos(pos->getX(), pos->getY());
		gameProps->addObject(g1);
	}
}

int Guy::checkDeath(GameProperties *gameProps)
{
	if (getPosition()->getY() > 7)
		return 1;
	return 0;
}