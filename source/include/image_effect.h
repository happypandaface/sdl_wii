#ifndef _IMAGE_EFFECT_H_
#define _IMAGE_EFFECT_H_

#include <SDL/SDL.h>

#define IMG_FX_DEFAULT_SPD 1.0f;

class ImageEffect
{
	public:
		ImageEffect();
		virtual ~ImageEffect();
		virtual void setTime(float);
		void apply(SDL_Rect *src, SDL_Rect *dst);
		virtual void applyRect(SDL_Rect *src, SDL_Rect *dst);
		void reset();
	protected:
		float time;
		float speed;
};
#endif