#include "player_indicator.h"

PlayerIndicator::PlayerIndicator(BaseObject *f, int n)
{
	toFollow = f;
	player_num = n;
	size->set(.5, .25);
}
void PlayerIndicator::load_animations(AnimationHolder *animHolder)
{
	if (player_num == 0)
	{
		setAnimation(animHolder->get_anim(ANIM_PLR_INDCTR_1));
	}else
	if (player_num == 1)
	{
		setAnimation(animHolder->get_anim(ANIM_PLR_INDCTR_2));
	}else
	if (player_num == 2)
	{
		setAnimation(animHolder->get_anim(ANIM_PLR_INDCTR_3));
	}else
	if (player_num == 3)
	{
		setAnimation(animHolder->get_anim(ANIM_PLR_INDCTR_4));
	}
}
void PlayerIndicator::playerDied(BaseObject *p)
{
	addType(TYP_DEAD);
}
int PlayerIndicator::simpleUpdate(float delta)
{
	if (!checkType(TYP_DEAD))
		setPos(toFollow->getPosition()->getX(), toFollow->getPosition()->getY()-getSize()->getY()*2);
	return 1;
}