#include "patroller.h"
#include <cmath>
#include <iostream>

#define TURN_AROUND_DIST 0.01f

struct PatrolPos
{
	Pos2 pos;
	float speed;
};

Patroller::Patroller()
{
	patrolPositions = NULL;
	numPositions = -1;
	numSet = 0;
	curPos = 0;
	addFromLast = 0;
}
Patroller::~Patroller()
{
	if (numPositions != -1)
		delete[] patrolPositions;
}
void Patroller::setNumPatrol(int num)
{
	if (numPositions != -1)
		delete[] patrolPositions;
	numPositions = num;
	numSet = 0;
	curPos = 0;
	patrolPositions = new PatrolPos[numPositions];
}
int Patroller::addPatrol(float x, float y, float speed)
{
	if (numSet < numPositions)
	{
		patrolPositions[numSet].pos.set(x, y);
		patrolPositions[numSet].speed = speed;
		++numSet;
		return 1;
	}
	return 0;
}
int Patroller::doPatrol(float delta)
{
	if (numSet > 0)
	{
		if (curPos >= numSet)
			curPos = 0;
		Pos2 dist;
		struct PatrolPos *curPatrol = &(patrolPositions[curPos]);
		dist.set(&(curPatrol->pos));
		dist.sub(getPosition());
		float length = dist.len();
		if (length < TURN_AROUND_DIST)
		{
			addFromLast = -length;
			pos->set(&(curPatrol->pos));
			++curPos;
			return 1;
		}else
		{
			dist.mul(1.0/length);
			dist.mul((curPatrol->speed+addFromLast)*delta);
			pos->add(&dist);
			addFromLast = 0;
			return 0;
		}
	}
	return -1;
}