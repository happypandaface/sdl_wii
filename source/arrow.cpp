#include "arrow.h"
#include <iostream>

Arrow::Arrow()
{
	size->set(.5, .25);
}

void Arrow::load_animations(AnimationHolder *animHolder)
{
	if (dir_facing & DIR_LEFT)
		setAnimation(animHolder->get_anim(ANIM_ARROW_LEFT));
	else
		setAnimation(animHolder->get_anim(ANIM_ARROW_RIGHT));
}