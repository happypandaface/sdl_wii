#include "animation.h"
#include <math.h>
#include "pos2.h"
#include <iostream>

AnimationFrame::AnimationFrame()
{
	num_images = 0;
	image_type = NULL;
	offset = NULL;
	time = 1;
	added_images = 0;
	num_effects = 0;
	added_effects = 0;
}
AnimationFrame::AnimationFrame(int ni)
{
	setNumImages(ni);
}
void AnimationFrame::setNumImages(int ni)
{
	if (image_type != NULL)
		delete[] image_type;
	if (offset != NULL)
		delete[] offset;
	num_images = ni;
	image_type = new int[num_images];
	offset = new Pos2[num_images];
	time = 1;
	added_images = 0;
}
AnimationFrame::~AnimationFrame()
{
	if (image_type != NULL)
		delete[] image_type;
	if (offset != NULL)
		delete[] offset;
	deleteEffects();
}
void AnimationFrame::setTime(float t)
{
	time = t;
}
float AnimationFrame::getTime()
{
	return time;
}
void AnimationFrame::setEffects(int i)
{
	deleteEffects();
	num_effects = i;
	added_effects = 0;
	effects = new ImageEffect*[num_effects];
}
void AnimationFrame::addEffect(ImageEffect *ie)
{
	effects[added_effects] = ie;
	++added_effects;
}
ImageEffect **AnimationFrame::getEffects()
{
	return effects;
}
ImageEffect *AnimationFrame::getEffect(int i)
{
	return effects[i];
}
int AnimationFrame::getEffectSize()
{
	return added_effects;
}
void AnimationFrame::deleteEffects()
{
	for (int i = 0; i < added_effects; ++i)
		delete effects[i];
	if (effects != NULL)
		delete[] effects;
	num_effects = 0;
	added_effects = 0;
}
void AnimationFrame::addImage(int img_type, float offsetX, float offsetY)
{
	image_type[added_images] = img_type;
	offset[added_images].set(offsetX, offsetY);
	++added_images;
}
int AnimationFrame::getNumImages()
{
	// this returns the images added, so that you
	// 	can allocated more memory than you need
	//	without breaking the animation system.
	return added_images;
}
int AnimationFrame::getImage(int num)
{
	if (num >= added_images)
		return -1;
	return image_type[num];
}
Pos2 *AnimationFrame::getOffset(int num)
{
	if (num >= added_images)
		return NULL;
	return &(offset[num]);
}

AnimationInstance::AnimationInstance(Animation *a)
{
	animation = a;
	timePer = 0;
	speed = animation->getBaseSpeed();
	maxLoops = animation->getMaxLoops();
	resetLoops();
}
AnimationInstance::~AnimationInstance()
{
	
}
int AnimationInstance::getTimesLooped()
{
	return timesLooped;
}
void AnimationInstance::reset()
{
	resetLoops();
	timePer = 0;
}
int AnimationInstance::resetLoops()
{
	timesLooped = 0;
	return timesLooped;
}
void AnimationInstance::setMaxLoops(int ml)
{
	maxLoops = ml;
}
void AnimationInstance::setSpeed(float spd)
{
	speed = spd;
}
void AnimationInstance::update(float delta)
{
	timePer += delta*speed;
	while (timePer > 1)
	{
		++timesLooped;
		timePer = 0;
	}
	if (maxLoops != -1 && timesLooped >= maxLoops)
		timePer = 1;
}
float AnimationInstance::getComplete()
{
	return timePer;
}
void AnimationInstance::draw(ResourceLoader *res_holder, SDL_Surface *screen, float x, float y)
{
	animation->draw(res_holder, screen, this, x, y);
}

Animation::Animation(int nf)
{
	numFrames = nf;
	totalTime = 0;
	frames = new AnimationFrame[numFrames];
	curFrame = 0;
	baseSpeed = 0;
	src_rect = new SDL_Rect;
	src_rect->x = 0;
	src_rect->y = 0;
	src_rect->w = 64;
	src_rect->h = 64;
	dst_rect = new SDL_Rect;
	dst_rect->x = 0;
	dst_rect->y = 0;
	dst_rect->w = 64;
	dst_rect->h = 64;
	baseLoop = -1;
}
Animation::~Animation()
{
	delete[] frames;
}
void Animation::setMaxLoops(int l)
{
	baseLoop = l;
}
int Animation::getMaxLoops()
{
	return baseLoop;
}
void Animation::setBaseSpeed(float bs)
{
	baseSpeed = bs;
}
float Animation::getBaseSpeed()
{
	return baseSpeed;
}
AnimationFrame *Animation::getNewframe()
{
	AnimationFrame *rtn = &(frames[curFrame]);
	curFrame++;
	return rtn;
}
void Animation::compileFrames()
{
	totalTime = 0;
	for (int i = 0; i < curFrame; ++i)
		totalTime += frames[i].getTime();
}
void Animation::addFrame(int img, float x, float y, float time)
{
	totalTime += time;
	frames[curFrame].setNumImages(1);
	frames[curFrame].addImage(img, x, y);
	frames[curFrame].setTime(time);
	++curFrame;
}
void Animation::draw(ResourceLoader *resLoader, SDL_Surface *screen, AnimationInstance *ai, float x, float y)
{
	AnimationFrame *currFrame = NULL;
	float cumulativeTime = 0;
	float timeThisFrame = 0;
	float timeInSeconds = ai->getComplete()*totalTime;
	for (int i = 0; i < numFrames; ++i)
	{
		if (timeInSeconds >= cumulativeTime)
		{
			timeThisFrame = timeInSeconds-cumulativeTime;
			currFrame = &(frames[i]);
		}else
		{
			break;
		}
		cumulativeTime += currFrame->getTime();
	}
	if (currFrame != NULL)
	{
		for (int i = 0; i < currFrame->getEffectSize(); ++i)
			currFrame->getEffect(i)->setTime(timeThisFrame);
		for (int i = 0; i < currFrame->getNumImages(); ++i)
		{
			Pos2 *offset = currFrame->getOffset(i);
			resLoader->draw_image(
				currFrame->getImage(i), 
				screen, x+offset->getX(), 
				y+offset->getY(), currFrame->getEffects(), currFrame->getEffectSize());
		}
	}
	//SDL_BlitSurface( resLoader->get_image(currFrame->image_type), src_rect, screen, dst_rect );
}