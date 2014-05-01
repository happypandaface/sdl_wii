#include "red_lazer.h"
#include "player.h"

RedLazer::RedLazer()
{
	size->set(.5, .25);
}

void RedLazer::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_RED_LAZER));
}

int RedLazer::each_object(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
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
	}
	return 0;
}