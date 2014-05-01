#include "stone_emblem.h"
#include "player.h"

StoneEmblem::StoneEmblem()
{
	active = 0;
	changedFireAnim = 1;
}

void StoneEmblem::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_STONE_EMBLEM));
}

int StoneEmblem::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	ObjectIterator *objIter = objHolder->getIterator();
	BaseObject *curr;
	while(objHolder->hasNext(objIter))
	{
		curr = objHolder->next(objIter);
		Player *plr = dynamic_cast<Player*>(curr);
		if (plr != NULL)
		{
			Pos2 *dst = pos->intersection(
				size, 
				curr->getPosition(), 
				curr->getSize());
			if (dst != NULL)
				gameProps->setActiveSpawn(this);
		}
	}
	objHolder->destroyIterator(objIter);
	if (active && !changedFireAnim)
	{
		setAnimation(gameProps->getAnimHolder()->get_anim(ANIM_STONE_EMBLEM_BURN));
		changedFireAnim = 1;
	}else
	if (!active && !changedFireAnim)
	{
		setAnimation(gameProps->getAnimHolder()->get_anim(ANIM_STONE_EMBLEM));
		changedFireAnim = 1;
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}

Pos2 *StoneEmblem::getSpawnPos()
{
	return getPosition();
}
void StoneEmblem::setActive()
{
	active = 1;
	changedFireAnim = 0;
}
void StoneEmblem::setInactive()
{
	active = 0;
	changedFireAnim = 0;
}