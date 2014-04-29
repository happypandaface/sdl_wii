#ifndef _ANIMATION_HOLDER_H_
#define _ANIMATION_HOLDER_H_

class AnimationHolder;

#include "animation.h"
#include "res_loader.h"

#define NUM_ANIMS 5

#define ANIM_SPIKE_BALL 1
#define ANIM_COOL_GUY_WALK 2
#define ANIM_BG 3
#define ANIM_DIRT_BLOCK 4
#define ANIM_GIBLET1 5

class AnimationHolder
{
	public:
		AnimationHolder();
		~AnimationHolder();
		void load(ResourceLoader *res_loader);
		Animation *get_anim(int anim_type);
	private:
		int get_arr_pos(int anim_type);
		Animation *anims[NUM_ANIMS];
};
#endif