#include "background.h"

void Background::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_BG));
}