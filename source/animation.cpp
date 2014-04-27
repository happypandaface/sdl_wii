#include "animation.h"
#include <math.h>
#include "pos2.h"

struct Frame
{
	int image_type;
	Pos2 offset;
};

AnimationInstance::AnimationInstance(Animation *a)
{
	animation = a;
	timePer = 0;
	speed = animation->getBaseSpeed();
}
AnimationInstance::~AnimationInstance()
{
	
}
void AnimationInstance::setSpeed(float spd)
{
	speed = spd;
}
void AnimationInstance::update(float delta)
{
	timePer += delta*speed;
	while (timePer > 1)
		--timePer;
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
	frames = new struct Frame[numFrames];
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
}
Animation::~Animation()
{
	delete[] frames;
}
void Animation::setBaseSpeed(float bs)
{
	baseSpeed = bs;
}
float Animation::getBaseSpeed()
{
	return baseSpeed;
}
void Animation::addFrame(int img, float x, float y)
{
	struct Frame *frame = new Frame;
	frame->image_type = img;
	frame->offset.setX(x);
	frame->offset.setY(y);
	frames[curFrame] = *frame;
	++curFrame;
}
void Animation::draw(ResourceLoader *resLoader, SDL_Surface *screen, AnimationInstance *ai, float x, float y)
{
	struct Frame *currFrame = &(frames[(int)floor(ai->getComplete()*numFrames)]);
	dst_rect->x = x+currFrame->offset.getX();
	dst_rect->y = y+currFrame->offset.getY();
	SDL_BlitSurface( resLoader->get_image(currFrame->image_type), src_rect, screen, dst_rect );
}