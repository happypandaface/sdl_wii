#include "animation_holder.h"

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
	spikes->addFrame(IMG_SPIKE_BALL1, 0, 0, 2);
	spikes->addFrame(IMG_SPIKE_BALL2, 0, 0, .1);
	spikes->addFrame(IMG_SPIKE_BALL3, 0, 0, .1);
	spikes->addFrame(IMG_SPIKE_BALL4, 0, 0, 2);
	spikes->addFrame(IMG_SPIKE_BALL3, 0, 0, .2);
	spikes->addFrame(IMG_SPIKE_BALL2, 0, 0, .2);
	spikes->setBaseSpeed(.6);
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
}
int AnimationHolder::get_arr_pos(int anim_type)
{
	return anim_type-1;
}
Animation *AnimationHolder::get_anim(int anim_type)
{
	return anims[get_arr_pos(anim_type)];
}