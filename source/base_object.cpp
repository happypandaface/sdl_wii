#include "base_object.h"
#include <iostream>
#include <stddef.h>

BaseObject::BaseObject()
{
	animInst = NULL;
	speed = 8;
	pos = new Pos2();
	size = new Pos2(1, 1);
	vel = new Pos2();
	hitDir = 0;
	types = 0;
	shouldBeRemoved = 0;
	restitution = 3;
}

BaseObject::~BaseObject()
{
	delete pos;
	delete size;
	delete vel;
}

void BaseObject::setPos(float x, float y)
{
	pos->setX(x);
	pos->setY(y);
}

void BaseObject::setAnimation(Animation *a)
{
	animInst = new AnimationInstance(a);
}

int BaseObject::checkHitDir(int hd)
{
	if (hitDir & hd)
		return true;
	return false;
}

int BaseObject::checkIfShouldBeRemoved()
{
	return shouldBeRemoved;
}
void BaseObject::setToBeRemoved(int remove)
{
	shouldBeRemoved = remove;
}

int BaseObject::load(ResourceLoader *resLoader)
{
	//spriteImage = resLoader->get_image(IMG_DIRT_SQUARE);
	//spriteImage = resLoader->get_image(IMG_TEST);
	return 1;
}

Pos2 *BaseObject::getPosition()
{
	return pos;
}

int BaseObject::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	hitDir = 0;
	if (checkType(TYP_CLIPS))
	{
		ObjectIterator *objIter = objHolder->getIterator();
		BaseObject *curr;
		while(objHolder->hasNext(objIter))
		{
			curr = objHolder->next(objIter);
			if (curr->checkType(TYP_SOLID))
			{
				Pos2 *dst = pos->intersection(
					size, 
					curr->getPosition(), 
					size);
				if (dst != NULL)
				{
					if (dst->getY() > 0){
						hitDir |= DIR_DOWN;
						if (dst->getY() > 0)
							vel->setY(0);
					}
					if (dst->getY() < 0){
						hitDir |= DIR_UP;
						if (dst->getY() < 0)
							vel->setY(0);
					}
					if (dst->getX() > 0){
						hitDir |= DIR_RIGHT;
						if (dst->getX() > 0)
							vel->setX(0);
					}
					if (dst->getX() < 0){
						hitDir |= DIR_LEFT;
						if (dst->getX() < 0)
							vel->setX(0);
					}
					pos->sub(dst);
					delete dst;
				}
			}
		}
		objHolder->destroyIterator(objIter);
	}
	//kinematic stuff
	pos->addMul(vel, delta);
	vel->mul(1-(restitution*delta));
	animInst->update(delta);
	return 1;
}

int BaseObject::checkType(long type)
{
	if (types & type)
		return true;
	return false;
}
void BaseObject::addType(long type)
{
	types |= type;
}
void BaseObject::removeType(long type)
{
	types &= ~type;
}

void BaseObject::doGravity(float strength, float delta)
{
	vel->addY(strength*delta);
}

int BaseObject::draw(ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen)
{
	/*
	SDL_Rect *src_rect = new SDL_Rect;
	src_rect->x = 0;
	src_rect->y = 0;
	src_rect->w = 64;
	src_rect->h = 64;
	SDL_Rect *dst_rect = new SDL_Rect;
	dst_rect->x = 0;
	dst_rect->y = 0;
	dst_rect->w = 64;
	dst_rect->h = 64;
	SDL_BlitSurface( resLoader->get_image(IMG_TEST), src_rect, screen, dst_rect );*/
	Pos2 *tileSize = gameProps->getTileSize();
	animInst->draw(resLoader, screen, pos->getX()*tileSize->getX(), pos->getY()*tileSize->getY());
	//SDL_BlitSurface( spriteImage, src_rect, screen, dst_rect );
	return 1;
}