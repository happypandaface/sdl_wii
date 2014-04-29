#include "giblet.h"
#include <stdlib.h>

Giblet::Giblet()
{
	addType(TYP_CLIPS);
	addType(TYP_HAS_GRAV);
	size->set(.5, .5);
	timeSinceStart = 0;
	vel->rnd()->sub(.5, 1.5)->mul(10);
	restitution = 1;
}

void Giblet::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_GIBLET1));
}

int Giblet::update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	timeSinceStart += delta;
	if (timeSinceStart > 5)
		addType(TYP_DEAD);
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}