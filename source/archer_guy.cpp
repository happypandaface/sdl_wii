#include "archer_guy.h"
#include "player.h"
#include "arrow.h"
#include <iostream>

ArcherGuy::ArcherGuy()
{
	addType(TYP_CLIPS);
	addType(TYP_HAS_GRAV);
	size->set(.5, .95);
	dir_facing = DIR_RIGHT;
	firingArrow = 0;
	fireArrowCount = 0;
	fireArrowCooldown = 0;
}
void ArcherGuy::die(BaseObject *killer)
{
	if (spawner != NULL)
		spawner->alertDeath(this);
	Guy::die(killer);
}
void ArcherGuy::setSpawner(BaseObject *s)
{
	spawner = s;
}
int ArcherGuy::each_object(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	Player *plr = dynamic_cast<Player*>(curr);
	if (plr != NULL)
	{
		Pos2 *dst = pos->intersection(
			size, 
			curr->getPosition(), 
			curr->getSize());
		if (dst)
		{
			die(this);
			curr->die(this);
			delete dst;
		}
		if (plr->getPosition()->getY() > getPosition()->getY() - plr->getSize()->getY() &&
			plr->getPosition()->getY() < getPosition()->getY() + size->getY() &&
			(
				(dir_facing & DIR_LEFT && plr->getPosition()->getX() < getPosition()->getX()) ||
				(dir_facing & DIR_RIGHT && plr->getPosition()->getX() > getPosition()->getX())
			))
		{
			if (fireArrowCooldown > ARROW_GUY_FIRE_COOLDOWN_2)
			{
				if (firingArrow == 0)
				{
					firingArrow = 1;
					fireArrowCount = 0;
					fireArrowCooldown = 0;
				}
			}
		}
	}
	return BaseObject::each_object(objHolder, gameProps, audioPlayer, contrlr, curr, delta);
}
int ArcherGuy::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (firingArrow == 1)
	{
		fireArrowCount += delta;
		if (dir_facing & DIR_LEFT)
		{
			if (cur_anim != ANIM_ARCHER_GUY_FIRE_LEFT)
				setAnimation(gameProps->getAnimHolder(), ANIM_ARCHER_GUY_FIRE_LEFT);
		}
		if (dir_facing & DIR_RIGHT)
		{
			if (cur_anim != ANIM_ARCHER_GUY_FIRE_RIGHT)
				setAnimation(gameProps->getAnimHolder(), ANIM_ARCHER_GUY_FIRE_RIGHT);
		}
		if (fireArrowCount > ARROW_GUY_FIRE_COOLDOWN)
		{
			setAnimation(gameProps->getAnimHolder(), ANIM_ARCHER_GUY_WALK_RIGHT);
			fireArrowCount = 0;
			firingArrow = 0;
			Arrow *bl = new Arrow();
			bl->setShooter(this);
			bl->setDirection(dir_facing);
			bl->load(gameProps->getResLoader(), gameProps->getAnimHolder());
			bl->setPos(getPosition()->getX(), getPosition()->getY());
			gameProps->addObject(bl);
		}
	}
	if (firingArrow == 0)
	{
		fireArrowCooldown += delta;
		Pos2 posDown;
		posDown.set(getPosition());
		posDown.addY(size->getY()+.3);
		Pos2 posAhead;
		posAhead.set(getPosition());
		posAhead.addY(size->getY()/2);
		if (dir_facing & DIR_LEFT)
		{
			posDown.addX(-.2);
			posAhead.addX(-.7);
		}else
		if (dir_facing & DIR_RIGHT)
		{
			posDown.addX(size->getX()+.2);
			posAhead.addX(size->getX()+.7);
		}
		if (BaseObject::checkExists(objHolder, &posDown, TYP_SOLID) == 0 ||
			BaseObject::checkExists(objHolder, &posAhead, TYP_SOLID | TYP_KILLS) == 1)
		{
			if (dir_facing & DIR_LEFT)
				dir_facing = DIR_RIGHT;
			else if (dir_facing & DIR_RIGHT)
				dir_facing = DIR_LEFT;
		}
		if (dir_facing & DIR_LEFT)
		{
			if (cur_anim != ANIM_ARCHER_GUY_WALK_LEFT)
				setAnimation(gameProps->getAnimHolder(), ANIM_ARCHER_GUY_WALK_LEFT);
			vel->setX(-1);
		}
		if (dir_facing & DIR_RIGHT)
		{
			if (cur_anim != ANIM_ARCHER_GUY_WALK_RIGHT)
				setAnimation(gameProps->getAnimHolder(), ANIM_ARCHER_GUY_WALK_RIGHT);
			vel->setX(1);
		}
		if (Guy::checkDeath(gameProps) == 1)
			die(NULL);
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}
void ArcherGuy::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder, ANIM_ARCHER_GUY_WALK_LEFT);
}