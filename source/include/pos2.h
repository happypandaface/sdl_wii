#ifndef _POS_2_H_
#define _POS_2_H_

#include <string>

#define DIR_DOWN 0b0001
#define DIR_RIGHT 0b0010
#define DIR_LEFT 0b0100
#define DIR_UP 0b1000

using namespace std;

class Pos2
{
	public:
		Pos2();
		Pos2(float x, float y);
		~Pos2();
		float getX();
		float getY();
		Pos2 *set(Pos2 *set);
		float setX(float x);
		float setY(float y);
		Pos2 *set(float x, float y);
		Pos2 *add(float x, float y);
		float addX(float x);
		float addY(float y);
		float subX(float x);
		float subY(float y);
		float mulX(float scl);
		float mulY(float scl);
		float len2();
		float len();
		Pos2 *nor();
		float dst2(Pos2 *other);
		float dst(Pos2 *other);
		Pos2 *rnd();
		Pos2 *addMul(Pos2 *add, float mul);
		Pos2 *div(Pos2 *div);
		Pos2 *mul(float scl);
		Pos2 *add(Pos2 *p);
		Pos2 *sub(Pos2 *p);
		Pos2 *sub(float x, float y);
		Pos2 *circRectIntersect(float offx, float offy, float radius, Pos2 *rectPos, Pos2 *rectSize);
		Pos2 *intersection(Pos2 *size1, Pos2 *pos2, Pos2 *size2);
		Pos2 *intersection(Pos2 *size1, Pos2 *pos2, Pos2 *size2, char canShoves);
		string toString();
	private:
		float x;
		float y;
};
#endif