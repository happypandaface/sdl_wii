#include "spike_ball.h"

int SpikeBall::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	Patroller::doPatrol(delta);
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		if (curr->checkType(TYP_CLIPS))
		{
			/*
			Pos2 *dst = pos->intersection(
				size, 
				curr->getPosition(), 
				curr->getSize());
			*/
			Pos2 *dst = pos->circRectIntersect(
				size->getX()/2,// this is the middle of the circle
				size->getY()/2,// this is the middle of the circle
				.3,// this is the radius
				curr->getPosition(), 
				curr->getSize());
			
			if (dst != NULL)
			{
				curr->die(this);
				delete dst;
			}
		}
	}
	objHolder->destroyIterator(objIter);
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}

void SpikeBall::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_SPIKE_BALL));
}