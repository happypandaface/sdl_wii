#ifndef _IMG_FX_CUT_H_
#define _IMG_FX_CUT_H_

#include "image_effect.h"

class ImgFxCut : public ImageEffect
{
	public:
		void applyRect(SDL_Rect *src, SDL_Rect *dst);
};
#endif