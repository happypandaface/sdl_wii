#include "game_properties.h"
#include "object_holder.h"
#include "background.h"
#include "spike_ball.h"
#include "stone_emblem.h"
#include "wall.h"
#include "wall_gun.h"
#include "finish_level.h"
#include "animation_holder.h"

void makeLevel1(GameProperties *gameProps, ObjectHolder *objHolder)
{
	Background *caveBg = new Background();
	caveBg->setBG(ANIM_BG);
	caveBg->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	caveBg->setLayer(-1);
	caveBg->setPos(-1, -1);
	gameProps->getCam()->addDrag(caveBg, 0.91);
	objHolder->addObject(caveBg);
	
	SpikeBall *sb = new SpikeBall();
	sb->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	sb->setPos(5, 5);
	objHolder->addObject(sb);
	
	SpikeBall *sb2 = new SpikeBall();
	sb2->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	sb2->setNumPatrol(2);
	sb2->addPatrol(10, 5, 1);
	sb2->addPatrol(10, 3, 1);
	sb2->setPos(10, 3);
	objHolder->addObject(sb2);
	
	SpikeBall *sb3 = new SpikeBall();
	sb3->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	sb3->setNumPatrol(2);
	sb3->addPatrol(12, 3, 1);
	sb3->addPatrol(12, 5, 1);
	sb3->setPos(12, 5);
	objHolder->addObject(sb3);
	
	StoneEmblem *firstSpawn = new StoneEmblem();
	firstSpawn->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	firstSpawn->setPos(1, 3);
	objHolder->addObject(firstSpawn);
	
	StoneEmblem *spawn2 = new StoneEmblem();
	spawn2->load(gameProps->getResLoader(), gameProps->getAnimHolder());
	spawn2->setPos(7, 3);
	objHolder->addObject(spawn2);
	
	{
		StoneEmblem *spawn = new StoneEmblem();
		spawn->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		spawn->setPos(15, 3);
		objHolder->addObject(spawn);
	}
	
	gameProps->setActiveSpawn(firstSpawn);
	
	for (int i = 0; i < 30; ++i)
	{
		Wall *w = new Wall();
		w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		w->setPos(i, 6);
		objHolder->addObject(w);
	}
	
	float puzz1StartX = 16;
	for (int i = 0; i < 1; ++i)
	{
		{
			Wall *w = new Wall();
			w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
			w->setPos(puzz1StartX+i, 5);
			objHolder->addObject(w);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		Wall *w = new Wall();
		w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		w->setPos(puzz1StartX+3, 4-i);
		objHolder->addObject(w);
	}
	{
		WallGun *wg = new WallGun();
		wg->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		wg->setPos(puzz1StartX+2.5, 4.25);
		objHolder->addObject(wg);
	}
	{
		StoneEmblem *spawn = new StoneEmblem();
		spawn->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		spawn->setPos(puzz1StartX+4, 3);
		objHolder->addObject(spawn);
	}
	
	float puzz2StartX = 24;
	for (int i = 0; i < 2; ++i)
	{
		{
			Wall *w = new Wall();
			w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
			w->setPos(puzz2StartX+i, 5);
			objHolder->addObject(w);
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		{
			Wall *w = new Wall();
			w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
			w->setPos(puzz2StartX+i, 2);
			objHolder->addObject(w);
		}
	}
	for (int i = 0; i < 4; ++i)
	{
		Wall *w = new Wall();
		w->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		w->setPos(puzz2StartX+3, 4-i);
		objHolder->addObject(w);
	}
	
	{
		WallGun *wg = new WallGun();
		wg->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		wg->setPos(puzz2StartX+2.5, 3.25);
		objHolder->addObject(wg);
	}
	{
		WallGun *wg = new WallGun();
		wg->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		wg->setPos(puzz2StartX+2.5, 4.25);
		objHolder->addObject(wg);
	}
	{
		FinishLevel *fl = new FinishLevel();
		fl->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		fl->setPos(puzz2StartX+5, 4);
		objHolder->addObject(fl);
	}
}