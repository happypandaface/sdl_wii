#include "game_properties.h"
#include "object_holder.h"
#include "background.h"
#include "spike_ball.h"
#include "stone_emblem.h"
#include "wall.h"
#include "wall_gun.h"
#include "finish_level.h"
#include "animation_holder.h"
#include "archer_guy.h"
#include "archer_guy_spawn.h"

void makeLevel2(GameProperties *gameProps, ObjectHolder *objHolder)
{
	Background *swampBg = new Background();
	swampBg->setBG(ANIM_SWAMP_BG);
	swampBg->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	swampBg->setLayer(-1);
	swampBg->setPos(-1, -1);
	gameProps->getCam()->addDrag(swampBg, 0.91);
	objHolder->addObject(swampBg);
	
	StoneEmblem *firstSpawn = new StoneEmblem();
	firstSpawn->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	firstSpawn->setPos(1, 3);
	objHolder->addObject(firstSpawn);
	
	{
		ArcherGuySpawn *aGuy = new ArcherGuySpawn();
		aGuy->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		aGuy->setPos(3, 4);
		objHolder->addObject(aGuy);
	}
	
	{
		StoneEmblem *spawn = new StoneEmblem();
		spawn->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		spawn->setPos(10, 3);
		objHolder->addObject(spawn);
	}
	
	gameProps->setActiveSpawn(firstSpawn);
	
	for (int i = -2; i < 11; ++i)
	{
		Wall *w = new Wall();
		w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		w->setPos(i, 6);
		objHolder->addObject(w);
	}
	for (int i = 3; i < 10; ++i)
	{
		Wall *w = new Wall();
		w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		w->setPos(i, 5);
		objHolder->addObject(w);
	}
	
}