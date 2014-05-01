#include "imgfx_cut.h"
#include <iostream>

void ImgFxCut::applyRect(SDL_Rect *src, SDL_Rect *dst)
{
	dst->h = dst->h*(1.0-time);
}