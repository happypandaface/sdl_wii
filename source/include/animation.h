#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "SDL/SDL.h"
#include "res_loader.h"
#include "pos2.h"


class AnimationFrame
{
	public:
		AnimationFrame();
		AnimationFrame(int ni);
		~AnimationFrame();
		void setNumImages(int n);
		void setTime(float t);
		float getTime();
		void addImage(int img_type, float offsetX, float offsetY);
		int getNumImages();
		int getImage(int i);
		Pos2 *getOffset(int i);
	private:
		int added_images;
		int num_images;
		int *image_type;
		float time;
		Pos2 *offset;
};

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
		AnimationFrame *getNewframe();
		void draw(ResourceLoader *res_holder, SDL_Surface *screen, AnimationInstance *ai, float x, float y);
	private:
		AnimationFrame *frames;
		SDL_Rect *src_rect;
		SDL_Rect *dst_rect;
		float totalTime;
		int curFrame;
		int numFrames;
		float baseSpeed;
};

#endif