#include "background.h"

Background::Background()
{
	img_bg = 0;
}
void Background::setBG(int bg)
{
	img_bg = bg;
}

void Background::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(img_bg));
}