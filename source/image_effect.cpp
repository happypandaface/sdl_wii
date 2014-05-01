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
void ImageEffect::apply(SDL_Rect *src, SDL_Rect *dst)
{
	applyRect(src, dst);
}
void ImageEffect::applyRect(SDL_Rect *src, SDL_Rect *dst)
{
	
}
void ImageEffect::reset()
{
	time = 0;
}