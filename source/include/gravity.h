#ifndef _GRAVITY_H_
#define _GRAVITY_H_
#include "object_holder.h"

class Gravity
{
	public:
		Gravity();
		~Gravity();
		void setStrength(float s);
		void update(ObjectHolder *objHolder, float delta);
	private:
		float strength;
};

#endif