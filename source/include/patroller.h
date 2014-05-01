#ifndef _PATROLLER_H_
#define _PATROLLER_H_

#include "base_object.h"
#include "pos2.h"

struct PatrolPos;

class Patroller : public BaseObject
{
	public:
		Patroller();
		virtual ~Patroller();
		virtual void setNumPatrol(int num);
		virtual int addPatrol(float x, float y, float speed);
	protected:
		virtual int doPatrol(float delta);
	private:
		int numPositions;
		int numSet;
		int curPos;
		float addFromLast;// thi sis to make everything sync up nicely
		PatrolPos *patrolPositions;
};

#endif