#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "SDL/SDL.h"
#include "res_loader.h"

struct Frame;

class Animation;

class AnimationInstance
{
	public:
		AnimationInstance(Animation *animation);
		~AnimationInstance();
		void setSpeed(float speed);
		void update(float delta);
		float getComplete();
		void draw(ResourceLoader *res_holder, SDL_Surface *screen, float x, float y);
	private:
		float speed;
		float timePer;
		Animation *animation;
};

class Animation
{
	public:
		Animation(int numFrames);
		~Animation();
		void setBaseSpeed(float bs);
		float getBaseSpeed();
		void addFrame(int img, float x, float y, float time);
		void draw(ResourceLoader *res_holder, SDL_Surface *screen, AnimationInstance *ai, float x, float y);
	private:
		struct Frame *frames;
		SDL_Rect *src_rect;
		SDL_Rect *dst_rect;
		float totalTime;
		int curFrame;
		int numFrames;
		float baseSpeed;
};

#endif