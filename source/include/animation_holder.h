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
/*
#define ANIM_DIRT_WALL_NE 13
#define ANIM_DIRT_WALL_NS 14
#define ANIM_DIRT_WALL_NW 15
#define ANIM_DIRT_WALL_ES 16
#define ANIM_DIRT_WALL_EW 17
#define ANIM_DIRT_WALL_SW 18
#define ANIM_DIRT_WALL_NES 19
#define ANIM_DIRT_WALL_ESW 20
#define ANIM_DIRT_WALL_SWN 21
#define ANIM_DIRT_WALL_WNE 22
#define ANIM_DIRT_WALL_ALL 23*/

#define NUM_ANIMS 12 // should be the last ANIM_ (assuming they're all incrementing correctly)

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