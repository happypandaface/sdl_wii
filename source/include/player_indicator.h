#ifndef _PLAYER_INDICATOR_H_
#define _PLAYER_INDICATOR_H_

#include "base_object.h"
#include "animation_holder.h"

class PlayerIndicator : public BaseObject
{
	public:
		PlayerIndicator(BaseObject *follow, int num);
		void load_animations(AnimationHolder *animHolder);
		int simpleUpdate(float delta);
		void playerDied(BaseObject *p);
	private:
		BaseObject *toFollow;
		int player_num;
};

#endif