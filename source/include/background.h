#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "base_object.h"

class Background : public BaseObject
{
	public:
		Background();
		void load_animations(AnimationHolder *animHolder);
		void setBG(int img_bg);
	private:
		int img_bg;
};

#endif