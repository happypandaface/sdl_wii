#include "image_effect.h"

ImageEffect::ImageEffect()
{
	time = 0;
	speed = IMG_FX_DEFAULT_SPD;
}
ImageEffect::~ImageEffect()
{
}
void ImageEffect::setTime(float t)
{
	time = t;
}
int ImageEffect::apply(SDL_Rect *src, SDL_Rect *dst)
{
	if (applyRect(src, dst) == 0)
		return 0;
	return 1;
}
int ImageEffect::applyRect(SDL_Rect *src, SDL_Rect *dst)
{
	return 0;
}
void ImageEffect::reset()
{
	time = 0;
}