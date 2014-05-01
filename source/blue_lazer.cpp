#include "blue_lazer.h"

BlueLazer::BlueLazer()
{
}

void BlueLazer::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_BLUE_LAZER));
}