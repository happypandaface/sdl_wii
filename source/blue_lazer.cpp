#include "blue_lazer.h"
#include "guy.h"

BlueLazer::BlueLazer()
{
	size->set(.5, .25);
}

int BlueLazer::each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	if (curr != shooter && dynamic_cast<Guy*>(curr))
	{
		Pos2 *dst = pos->intersection(
			size, 
			curr->getPosition(), 
			curr->getSize());
		if (dst)
		{
			curr->die(this);
			die(this);
			delete dst;
		}
	}
	return 1;
}

void BlueLazer::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_BLUE_LAZER));
}