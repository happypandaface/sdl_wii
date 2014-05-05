#include "imgfx_cut.h"
#include <iostream>

int ImgFxCut::applyRect(SDL_Rect *src, SDL_Rect *dst)
{
	src->h = src->h*(1.0-time);
	dst->h = dst->h*(1.0-time);
	return 0;
}