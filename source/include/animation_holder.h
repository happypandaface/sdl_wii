#ifndef _ANIMATION_HOLDER_H_
#define _ANIMATION_HOLDER_H_

class AnimationHolder;

#include "animation.h"
#include "res_loader.h"

#define ANIM_SPIKE_BALL 1
#define ANIM_COOL_GUY_WALK 2
#define ANIM_BG 3
#define ANIM_DIRT_BLOCK 4
#define ANIM_GIBLET1 5
#define ANIM_STONE_EMBLEM 6
#define ANIM_STONE_EMBLEM_BURN 7
#define ANIM_WALL_GUN 8
#define ANIM_DIRT_WALL_N 9
#define ANIM_DIRT_WALL_E 10
#define ANIM_DIRT_WALL_S 11
#define ANIM_DIRT_WALL_W 12
#define ANIM_PLR_INDCTR_1 13
#define ANIM_PLR_INDCTR_2 14
#define ANIM_PLR_INDCTR_3 15
#define ANIM_PLR_INDCTR_4 16
#define ANIM_BLUE_LAZER 17
#define ANIM_COOL_GUY_WALK_LEFT 18
#define ANIM_COOL_GUY_WALK_RIGHT 19
#define ANIM_COOL_GUY_STAND_LEFT 20
#define ANIM_COOL_GUY_STAND_RIGHT 21
#define ANIM_RED_LAZER 22

#define NUM_ANIMS 22 // should be the last ANIM_ (assuming they're all incrementing correctly)

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