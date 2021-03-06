#include "base_object.h"
#include <iostream>
#include <stddef.h>

BaseObject::BaseObject()
{
	canShoves = ~0;// can shove in any direction
	animInst = NULL;
	speed = 8;
	pos = new Pos2();
	size = new Pos2(1, 1);
	vel = new Pos2();
	offset = new Pos2();
	hitDir = 0;
	types = 0;
	shouldBeRemoved = 0;
	restitution = 3;
	layer = 0;
	dir_facing = 0;
	timeSinceStart = 0;
	cooldown = 0;
	cur_anim = 0;
}

BaseObject::~BaseObject()
{
	delete pos;
	delete size;
	delete vel;
	delete offset;
	delete animInst;
}
void BaseObject::setDirection(char dir)
{
	dir_facing = dir;
}

void BaseObject::setPos(float x, float y)
{
	pos->setX(x);
	pos->setY(y);
}
void BaseObject::alertDeath(BaseObject *died)
{
}

void BaseObject::setAnimation(Animation *a)
{
	if (animInst != NULL)
		delete animInst;
	animInst = new AnimationInstance(a);
}

void BaseObject::setAnimation(AnimationHolder *animHolder, int anim)
{
	cur_anim = anim;
	setAnimation(animHolder->get_anim(anim));
}

int BaseObject::checkHitDir(int hd)
{
	if (hitDir & hd)
		return true;
	return false;
}

void BaseObject::doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
}

int BaseObject::checkIfShouldBeRemoved()
{
	return shouldBeRemoved;
}
void BaseObject::setToBeRemoved(int remove)
{
	shouldBeRemoved = remove;
}

int BaseObject::load(ResourceLoader *resLoader, AnimationHolder *animHolder)
{
	//spriteImage = resLoader->get_image(IMG_DIRT_SQUARE);
	//spriteImage = resLoader->get_image(IMG_TEST);
	load_animations(animHolder);
	return 1;
}

void BaseObject::load_animations(AnimationHolder *animHolder)
{
	// to be overriden.
}

Pos2 *BaseObject::getPosition()
{
	return pos;
}
void BaseObject::setOffset(float x, float y)
{
	offset->set(x, y);
}


int BaseObject::each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	// override for easy stuff
	return 0;
}
char BaseObject::getShoves()
{
	return canShoves;
}

int BaseObject::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	timeSinceStart += delta;// for things that remove themselves after a while,
		// or explode or whatever
	if (cooldown > 0)
		cooldown -= delta;
	simpleUpdate(delta);
	//kinematic stuff
	pos->addMul(vel, delta);
	vel->mul(1-(restitution*delta));
	animInst->update(delta);
	//reset the hit dir
	hitDir = 0;
	if (checkType(TYP_CLIPS) || checkType(TYP_HITS))
	{
		ObjectIterator *objIter = objHolder->getIterator();
		BaseObject *curr;
		while(objHolder->hasNext(objIter))
		{
			curr = objHolder->next(objIter);
			each_object(objHolder, gameProps,  audioPlayer, contrlr, curr, delta);
			if (checkType(TYP_CLIPS) && curr->checkType(TYP_SOLID))
			{
				Pos2 *dst = pos->intersection(
					size, 
					curr->getPosition(), 
					curr->size,
					curr->getShoves());
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
	return 1;
}
int BaseObject::checkExists(ObjectHolder *objHolder, Pos2 *loc, long type)
{
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	Pos2 size(0, 0);
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		if (curr->checkType(type))
		{
			Pos2 *dst = loc->intersection(
				&size,
				curr->getPosition(), 
				curr->size);
			if (dst != NULL)
			{
				delete dst;
				return 1;
			}
		}
	}
	objHolder->destroyIterator(objIter);
	return 0;
}
int BaseObject::simpleUpdate(float delta)
{
	
	return 1;
}

Pos2 *BaseObject::getSize()
{
	return size;
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
int BaseObject::getLayer()
{
	return layer;
}
void BaseObject::setLayer(int l)
{
	layer = l;
}
void BaseObject::die(BaseObject *killer)
{
	
}
void BaseObject::setSpeed(float s)
{
	speed = s;
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
	//SDL_BlitSurface( spriteImage, src_rect, screen, dst_rect );
	
	Pos2 *tileSize = gameProps->getTileSize();
	
	return doDraw(
		(pos->getX()-gameProps->getOffset()->getX()+offset->getX())*(tileSize->getX()),
		(pos->getY()-gameProps->getOffset()->getY()+offset->getY())*(tileSize->getY()),
		resLoader, gameProps, screen);
}

int BaseObject::doDraw(float x, float y, ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen)
{
	if (animInst != NULL)
	{
		animInst->draw(
			resLoader, 
			screen, 
			x, 
			y
		);
	}
	return 1;
}