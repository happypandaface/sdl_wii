#include "pos2.h"
#include <cmath>
#include <stddef.h>
#include <sstream>

Pos2::Pos2()
{
	this->x = 0;
	this->y = 0;
}

Pos2::Pos2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Pos2::~Pos2()
{
}

string Pos2::toString()
{
	ostringstream ss;
	ss << this->x << ", " << this->y;
	return ss.str();
}

float Pos2::getX()
{
	this->x = x;
	return x;
}
float Pos2::getY()
{
	this->y = y;
	return y;
}
float Pos2::len2()
{
	return this->x*this->x+this->y*this->y;
}
float Pos2::len()
{
	return sqrt(len2());
}
float Pos2::mulX(float scl)
{
	this->x *= scl;
}
float Pos2::mulY(float scl)
{
	this->y *= scl;
}
Pos2 *Pos2::mul(float scl)
{
	mulX(scl);
	mulY(scl);
	return this;
}
float Pos2::setX(float x)
{
	this->x = x;
	return x;
}
float Pos2::setY(float y)
{
	this->y = y;
	return y;
}
float Pos2::addX(float x)
{
	this->x += x;
	return x;
}
float Pos2::addY(float y)
{
	this->y += y;
	return y;
}
float Pos2::subX(float x)
{
	this->x -= x;
	return x;
}
float Pos2::subY(float y)
{
	this->y -= y;
	return y;
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

Pos2 *Pos2::intersection(Pos2 *size1, Pos2 *pos2, Pos2 *size2)
{
	if (this->x + size1->x > pos2->x &&
		this->y + size1->y > pos2->y &&
		this->x < pos2->x + size2->x &&
		this->y < pos2->y + size2->y)
	{
		float distX1 = (this->x + size1->x) - pos2->x;
		float distX2 = (this->x - size2->x) - pos2->x;
		float distY1 = (this->y + size1->y) - pos2->y;
		float distY2 = (this->y - size2->y) - pos2->y;
		float distX = distX1;
		float distY = distY1;
		if (abs(distX2) < abs(distX1))
			distX = distX2;
		if (abs(distY2) < abs(distY1))
			distY = distY2;
		Pos2 *rtn = new Pos2();
		if (abs(distY) < abs(distX))
		{
			rtn->setY(distY);
			rtn->setX(0);
		}else
		{
			rtn->setX(distX);
			rtn->setY(0);
		}
		return rtn;
	}
	return NULL;
}