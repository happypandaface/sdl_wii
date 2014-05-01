#include "finish_level.h"
#include "player.h"

FinishLevel::FinishLevel()
{
	ending_level = 0;
	ending_level_time = 0;
}
void FinishLevel::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder, ANIM_FINISH_LEVEL);
	addType(TYP_HITS);
	size->set(2, 2);
}
int FinishLevel::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (ending_level_time > 100)
	{
		gameProps->endLevel();
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}
int FinishLevel::each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	if (ending_level)
	{
		ending_level_time += delta;
	}else
	{
		Player *plr = dynamic_cast<Player*>(curr);
		if (plr != NULL)
		{
			Pos2 *dst = pos->circRectIntersect(
				size->getX()/2,// this is the middle of the circle
				size->getY()/2,// this is the middle of the circle
				size->len()/8,// this is the radius
				curr->getPosition(), 
				curr->getSize());
			if (dst)
			{
				ending_level = 1;
				gameProps->freeze();
				addType(TYP_UNFRZN);
				
				ObjectIterator *objIter = objHolder->getIterator();
				BaseObject *curr;
				while(objHolder->hasNext(objIter))
				{
					curr = objHolder->next(objIter);
					Player *plrAlso = dynamic_cast<Player*>(curr);
					if (plrAlso != NULL)
					{
						plrAlso->addType(TYP_UNFRZN);
						plrAlso->endLevel(gameProps);
					}
				}
				objHolder->destroyIterator(objIter);
				delete dst;
			}
		}
	}
	return BaseObject::each_object(objHolder, gameProps, audioPlayer, contrlr, curr, delta);
}