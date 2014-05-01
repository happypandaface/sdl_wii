#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "pos2.h"

class Spawner
{
	public:
		virtual Pos2 *getSpawnPos()=0;
		virtual void setActive()=0;
		virtual void setInactive()=0;
};

#endif