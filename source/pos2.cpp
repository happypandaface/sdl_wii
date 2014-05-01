#include "pos2.h"
#include <cmath>
#include <stddef.h>
#include <sstream>
#include <stdlib.h>

Pos2::Pos2()
{
	x = 0;
	y = 0;
}

Pos2::Pos2(float x, float y)
{
	setX(x);
	setY(y);
}

Pos2::~Pos2()
{
}

float Pos2::dst2(Pos2 *other)
{
	float distX = getX()-other->getX();
	float distY = getY()-other->getY();
	return (distX*distX+distY+distY);
}

Pos2 *Pos2::nor()
{
	float length = len();
	if (length == 0)
		return NULL;
	mul(1.0/length);
	return this;
}

float Pos2::dst(Pos2 *other)
{
	return sqrt(dst2(other));
}

string Pos2::toString()
{
	ostringstream ss;
	ss << x << ", " << y;
	return ss.str();
}

float Pos2::getX()
{
	x = x;
	return x;
}
float Pos2::getY()
{
	y = y;
	return y;
}
float Pos2::len2()
{
	return x*x+y*y;
}
float Pos2::len()
{
	return sqrt(len2());
}
float Pos2::mulX(float scl)
{
	x *= scl;
	return x;
}
float Pos2::mulY(float scl)
{
	y *= scl;
	return y;
}
Pos2 *Pos2::mul(float scl)
{
	mulX(scl);
	mulY(scl);
	return this;
}
Pos2 *Pos2::div(Pos2 *div)
{
	mulX(1/div->getX());
	mulY(1/div->getY());
	return this;
}
Pos2 *Pos2::set(Pos2 *set)
{
	setX(set->getX());
	setY(set->getY());
	return this;
}
float Pos2::setX(float x)
{
	this->x = x;
	return this->x;
}
float Pos2::setY(float y)
{
	this->y = y;
	return this->y;
}
Pos2 *Pos2::add(float x, float y)
{
	addX(x);
	addY(y);
	return this;
}
float Pos2::addX(float x)
{
	this->x += x;
	return this->x;
}
float Pos2::addY(float y)
{
	this->y += y;
	return this->y;
}
float Pos2::subX(float x)
{
	this->x -= x;
	return this->x;
}
float Pos2::subY(float y)
{
	this->y -= y;
	return this->y;
}

Pos2 *Pos2::add(Pos2 *p)
{
	addX(p->getX());
	addY(p->getY());
	return this;
}

Pos2 *Pos2::sub(Pos2 *p)
{
	subX(p->getX());
	subY(p->getY());
	return this;
}
Pos2 *Pos2::addMul(Pos2 *add, float mul)
{
	addX(add->getX()*mul);
	addY(add->getY()*mul);
	return this;
}
Pos2 *Pos2::set(float x, float y)
{
	setX(x);
	setY(y);
	return this;
}
Pos2 *Pos2::rnd()
{
	setX(((float)(rand()%100))/100.0);
	setY(((float)(rand()%100))/100.0);
	return this;
}
Pos2 *Pos2::sub(float x, float y)
{
	subX(x);
	subY(y);
	return this;
}

// this currently returns a pos2 because I think it should calc stuff in the future,
// but for now it just does a simple calculation
Pos2 *Pos2::circRectIntersect(float offx, float offy, float radius, Pos2 *rectPos, Pos2 *rectSize)
{
	if (x+offx + radius >= rectPos->x &&
		y+offy + radius >= rectPos->y &&
		x+offx - radius <= rectPos->x + rectSize->x &&
		y+offy - radius <= rectPos->y + rectSize->y)
	{// the hit boxes collide, but this is a circle
		// so it could be in one of the 4 corners of the rectangle
		// around the circle, where it wouldn't hit.
		// check that:
		if (rectPos->x < x+offx &&
			rectPos->x+rectSize->x > x+offx)
			return new Pos2();
		if (rectPos->y < y+offy &&
			rectPos->y+rectSize->y > y+offy)
			return new Pos2();
		// now just check the distance to all 4 courners,
		// (this could be done faster by calculating which
		// corner we should check)
		Pos2 distPos;
		Pos2 cornerPos;
		{// first Corner:
			float dist = distPos.set(this)->add(offx, offy)->sub(rectPos)->len();
			if (dist < radius)
				return new Pos2();
		}
		{// second Corner now it's getting harder!:
			cornerPos.set(rectPos)->addX(rectSize->getX());
			float dist = distPos.set(this)->add(offx, offy)->sub(&cornerPos)->len();
			if (dist < radius)
				return new Pos2();
		}
		{// third Corner omg what?!?!:
			cornerPos.set(rectPos)->addY(rectSize->getY());
			float dist = distPos.set(this)->add(offx, offy)->sub(&cornerPos)->len();
			if (dist < radius)
				return new Pos2();
		}
		{// fourth Corner OMMMMGGGEEEEEWWWTFFFBBBQQQQQWTF~!!!!!11!
			cornerPos.set(rectPos)->add(rectSize);
			float dist = distPos.set(this)->add(offx, offy)->sub(&cornerPos)->len();
			if (dist < radius)
				return new Pos2();
		}
	}
	return NULL;
}

Pos2 *Pos2::intersection(Pos2 *size1, Pos2 *pos2, Pos2 *size2)
{
	return intersection(size1, pos2, size2, ~((char) 0));
}

// intersection is used to tell what + or - cardinal direction is the fastest out
// of a rectangle, given another rectangle.
// it's used for collision testing and clipping (push out of wall)
// if walls should be flush with eachother (and directly next to eachother),
//  they shouldn't push things out into the other one.
// this is where "canShoves" comes in
// it tell the method which directions are legal to push the rect out.
// kinda confusing :/
Pos2 *Pos2::intersection(Pos2 *size1, Pos2 *pos2, Pos2 *size2, char canShoves)
{
	if (x + size1->x >= pos2->x &&
		y + size1->y >= pos2->y &&
		x <= pos2->x + size2->x &&
		y <= pos2->y + size2->y)
	{
		float distX1 = (x + size1->x) - pos2->x;
		float distX2 = (x - size2->x) - pos2->x;
		float distY1 = (y + size1->y) - pos2->y;
		float distY2 = (y - size2->y) - pos2->y;
		// this stuff is complicated:
		// it always is...
		// so canShove is 4 bools to tell which directions should
		// be legal to push
		if (canShoves & DIR_RIGHT && 
			(abs(distX2) < abs(distX1) || ~canShoves & DIR_LEFT) &&
			(abs(distX2) < abs(distY1) || ~canShoves & DIR_UP) &&
			(abs(distX2) < abs(distY2) || ~canShoves & DIR_DOWN))
		{
			return new Pos2(distX2, 0);
		}else
		if (canShoves & DIR_LEFT && 
			(abs(distX1) < abs(distX2) || ~canShoves & DIR_RIGHT) &&
			(abs(distX1) < abs(distY1) || ~canShoves & DIR_UP) &&
			(abs(distX1) < abs(distY2) || ~canShoves & DIR_DOWN))
		{
			return new Pos2(distX1, 0);
		}else
		if (canShoves & DIR_UP && 
			(abs(distY1) < abs(distX2) || ~canShoves & DIR_RIGHT) &&
			(abs(distY1) < abs(distX1) || ~canShoves & DIR_LEFT) &&
			(abs(distY1) < abs(distY2) || ~canShoves & DIR_UP))
		{
			return new Pos2(0, distY1);
		}else
		if (canShoves & DIR_DOWN && 
			(abs(distY2) < abs(distX2) || ~canShoves & DIR_RIGHT) &&
			(abs(distY2) < abs(distX1) || ~canShoves & DIR_LEFT) &&
			(abs(distY2) < abs(distY1) || ~canShoves & DIR_DOWN))
		{
			return new Pos2(0, distY2);
		}
	}
	return NULL;
}