#include "animation_holder.h"
#include "imgfx_cut.h"

AnimationHolder::AnimationHolder()
{
	for (int i = 0; i < NUM_ANIMS; ++i)
		anims[i] = NULL;
}
AnimationHolder::~AnimationHolder()
{
	for (int i = 0; i < NUM_ANIMS; ++i)
		if (anims[i] != NULL)
		{
			delete anims[i];
			anims[i] = NULL;
		}
}

void AnimationHolder::load(ResourceLoader *res_loader)
{
	Animation *bg = new Animation(2);
	bg->addFrame(IMG_CAVE_BG, 0, 0, 1);
	bg->addFrame(IMG_CAVE_BG, 0, 0, 1);
	bg->setBaseSpeed(.2);
	anims[get_arr_pos(ANIM_BG)] = bg;
	
	Animation *a1 = new Animation(2);
	a1->addFrame(IMG_COOL_GUY2, 0, 0, 1);
	a1->addFrame(IMG_COOL_GUY, 0, 0, 1);
	a1->setBaseSpeed(.4);
	anims[get_arr_pos(ANIM_COOL_GUY_WALK)] = a1;
	
	Animation *spikes = new Animation(6);
	spikes->addFrame(IMG_SPIKE_BALL1, 0, 0, .4);
	spikes->addFrame(IMG_SPIKE_BALL2, 0, 0, .1);
	spikes->addFrame(IMG_SPIKE_BALL3, 0, 0, .1);
	spikes->addFrame(IMG_SPIKE_BALL4, 0, 0, .4);
	spikes->addFrame(IMG_SPIKE_BALL3, 0, 0, .2);
	spikes->addFrame(IMG_SPIKE_BALL2, 0, 0, .2);
	spikes->setBaseSpeed(2);
	anims[get_arr_pos(ANIM_SPIKE_BALL)] = spikes;
	
	Animation *a2 = new Animation(2);
	a2->addFrame(IMG_DIRT_SQUARE, 0, 0, 1);
	a2->addFrame(IMG_DIRT_SQUARE, 0, 0, 1);
	a2->setBaseSpeed(.2);
	anims[get_arr_pos(ANIM_DIRT_BLOCK)] = a2;
	
	Animation *giblet = new Animation(2);
	giblet->addFrame(IMG_GIBLET1, 0, 0, 1);
	giblet->setBaseSpeed(.2);
	anims[get_arr_pos(ANIM_GIBLET1)] = giblet;
	
	Animation *stoneEmblem = new Animation(1);
	stoneEmblem->addFrame(IMG_STONE_EMBLEM3, 0, 0, 1);
	stoneEmblem->setBaseSpeed(2);
	anims[get_arr_pos(ANIM_STONE_EMBLEM)] = stoneEmblem;
	
	Animation *stoneEmblemBurn = new Animation(8);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM2, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM4, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM1, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM2, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM4, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM2, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM1, 0, 0, 1);
	stoneEmblemBurn->addFrame(IMG_STONE_EMBLEM4, 0, 0, 1);
	stoneEmblemBurn->setBaseSpeed(1.1);
	anims[get_arr_pos(ANIM_STONE_EMBLEM_BURN)] = stoneEmblemBurn;
	
	Animation *wallGun = new Animation(1);
	wallGun->addFrame(IMG_WALL_GUN, 0, 0, 1);
	wallGun->setBaseSpeed(2);
	anims[get_arr_pos(ANIM_WALL_GUN)] = wallGun;
	
	Animation *dirtWall_N_ = new Animation(1);
	AnimationFrame *dirtWall_N_1 = dirtWall_N_->getNewframe();
	dirtWall_N_1->setNumImages(1);
	dirtWall_N_1->addImage(IMG_DIRT_SQUARE_NORTH, 0, 0);
	dirtWall_N_1->setTime(1);
	dirtWall_N_->setBaseSpeed(0);
	anims[get_arr_pos(ANIM_DIRT_WALL_N)] = dirtWall_N_;
	
	Animation *dirtWall_E_ = new Animation(1);
	AnimationFrame *dirtWall_E_1 = dirtWall_E_->getNewframe();
	dirtWall_E_1->setNumImages(1);
	dirtWall_E_1->addImage(IMG_DIRT_SQUARE_EAST, 0, 0);
	dirtWall_E_1->setTime(1);
	dirtWall_E_->setBaseSpeed(0);
	anims[get_arr_pos(ANIM_DIRT_WALL_E)] = dirtWall_E_;
	
	Animation *dirtWall_S_ = new Animation(1);
	AnimationFrame *dirtWall_S_1 = dirtWall_S_->getNewframe();
	dirtWall_S_1->setNumImages(1);
	dirtWall_S_1->addImage(IMG_DIRT_SQUARE_SOUTH, 0, 0);
	dirtWall_S_1->setTime(1);
	dirtWall_S_->setBaseSpeed(0);
	anims[get_arr_pos(ANIM_DIRT_WALL_S)] = dirtWall_S_;
	
	Animation *dirtWall_W_ = new Animation(1);
	AnimationFrame *dirtWall_W_1 = dirtWall_W_->getNewframe();
	dirtWall_W_1->setNumImages(1);
	dirtWall_W_1->addImage(IMG_DIRT_SQUARE_WEST, 0, 0);
	dirtWall_W_1->setTime(1);
	dirtWall_W_->setBaseSpeed(0);
	anims[get_arr_pos(ANIM_DIRT_WALL_W)] = dirtWall_W_;
	
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_PLR_INDCTR_1, 0, 0, 1);
		anim->setBaseSpeed(0);
		anims[get_arr_pos(ANIM_PLR_INDCTR_1)] = anim;
	}
	
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_PLR_INDCTR_2, 0, 0, 1);
		anim->setBaseSpeed(0);
		anims[get_arr_pos(ANIM_PLR_INDCTR_2)] = anim;
	}
	
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_PLR_INDCTR_3, 0, 0, 1);
		anim->setBaseSpeed(0);
		anims[get_arr_pos(ANIM_PLR_INDCTR_3)] = anim;
	}
	
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_PLR_INDCTR_4, 0, 0, 1);
		anim->setBaseSpeed(0);
		anims[get_arr_pos(ANIM_PLR_INDCTR_4)] = anim;
	}
	
	{
		Animation *anim = new Animation(3);
		anim->addFrame(IMG_BLUE_LAZER_1, 0, 0, 1);
		anim->addFrame(IMG_BLUE_LAZER_2, 0, 0, 1);
		anim->addFrame(IMG_BLUE_LAZER_3, 0, 0, 1);
		anim->setBaseSpeed(5);
		anims[get_arr_pos(ANIM_BLUE_LAZER)] = anim;
	}
	{
		Animation *anim = new Animation(3);
		anim->addFrame(IMG_RED_LAZER_1, 0, 0, 1);
		anim->addFrame(IMG_RED_LAZER_2, 0, 0, 1);
		anim->addFrame(IMG_RED_LAZER_3, 0, 0, 1);
		anim->setBaseSpeed(5);
		anims[get_arr_pos(ANIM_RED_LAZER)] = anim;
	}
	
	float subY = -10;
	{
		Animation *anim = new Animation(2);
		anim->addFrame(IMG_COOL_GUY_WALK_RIGHT_1, 0, subY, 1);
		anim->addFrame(IMG_COOL_GUY_WALK_RIGHT_2, 0, subY, 1);
		anim->setBaseSpeed(2.5);
		anims[get_arr_pos(ANIM_COOL_GUY_WALK_RIGHT)] = anim;
	}
	{
		Animation *anim = new Animation(2);
		anim->addFrame(IMG_COOL_GUY_WALK_LEFT_1, 0, subY, 1);
		anim->addFrame(IMG_COOL_GUY_WALK_LEFT_2, -5, subY, 1);
		anim->setBaseSpeed(2.5);
		anims[get_arr_pos(ANIM_COOL_GUY_WALK_LEFT)] = anim;
	}
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_COOL_GUY_STAND_LEFT, -5, -5+subY, 1);
		anim->setBaseSpeed(2.5);
		anims[get_arr_pos(ANIM_COOL_GUY_STAND_LEFT)] = anim;
	}
	{
		Animation *anim = new Animation(1);
		anim->addFrame(IMG_COOL_GUY_STAND_RIGHT, 0, subY, 1);
		anim->setBaseSpeed(2.5);
		anims[get_arr_pos(ANIM_COOL_GUY_STAND_RIGHT)] = anim;
	}
	{
		Animation *anim = new Animation(1);
		AnimationFrame *aFrame = anim->getNewframe();
		aFrame->setNumImages(1);
		aFrame->addImage(IMG_COOL_GUY_STAND_LEFT, -5, -5+subY);
		aFrame->setTime(1);
		aFrame->setEffects(1);
		ImgFxCut *imgCut = new ImgFxCut();
		aFrame->addEffect(imgCut);
		anim->setBaseSpeed(1);
		anim->setMaxLoops(1);
		anims[get_arr_pos(ANIM_PLAYER_CUT_UP_LEFT)] = anim;
	}
	{
		Animation *anim = new Animation(1);
		{
			AnimationFrame *aFrame = anim->getNewframe();
			aFrame->setNumImages(1);
			aFrame->addImage(IMG_COOL_GUY_STAND_RIGHT, 0, subY);
			aFrame->setTime(1);
			aFrame->setEffects(1);
			ImgFxCut *imgCut = new ImgFxCut();
			aFrame->addEffect(imgCut);
		}
		anim->compileFrames();
		anim->setBaseSpeed(1);
		anim->setMaxLoops(1);
		anims[get_arr_pos(ANIM_PLAYER_CUT_UP_RIGHT)] = anim;
	}
	{
		Animation *anim = new Animation(8);
		anim->addFrame(IMG_FINISH_LEVEL_1, 0, 0, 1);
		anim->addFrame(IMG_FINISH_LEVEL_3, 0, 0, 1);
		anim->addFrame(IMG_FINISH_LEVEL_4, 0, 0, 1);
		anim->addFrame(IMG_FINISH_LEVEL_5, 0, 0, 1);
		anim->addFrame(IMG_FINISH_LEVEL_6, 0, 0, 1);
		anim->addFrame(IMG_FINISH_LEVEL_7, 0, 0, 1);
		anim->setBaseSpeed(.5);
		anims[get_arr_pos(ANIM_FINISH_LEVEL)] = anim;
	}
}
int AnimationHolder::get_arr_pos(int anim_type)
{
	return anim_type-1;
}
Animation *AnimationHolder::get_anim(int anim_type)
{
	return anims[get_arr_pos(anim_type)];
}