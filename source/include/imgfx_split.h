#ifndef _IMG_FX_SPLIT_H_
#define _IMG_FX_SPLIT_H_

#include "image_effect.h"
#include "pos2.h"

class ImgFxSplit : public ImageEffect
{
	public:
		ImgFxSplit(int x, int y, int w, int h);
		int applyRect(SDL_Rect *src, SDL_Rect *dst);
	private:
		Pos2 start;
		Pos2 size;
};
#endif