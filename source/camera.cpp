#include "camera.h"
#include <iostream>

Camera::Camera(GameProperties *gp, float d)
{
	distance = d;
	camPos = new Pos2();
	for (int i = 0; i < MAX_FOLLOW; ++i)
		following[i] = NULL;
	for (int i = 0; i < MAX_DRAG; ++i)
	{
		dragging[i] = NULL;
		dragAmnts[i] = 0;
	}
}
Camera::~Camera()
{
	
}
void Camera::addFollow(BaseObject *bObj)
{
	for (int i = 0; i < MAX_FOLLOW; ++i)
		if (following[i] == NULL)
		{
			following[i] = bObj;
			return;
		}else if (following[i] == bObj)
		{
			return;
		}
}
void Camera::removeFollow(BaseObject *bObj)
{
	for (int i = 0; i < MAX_FOLLOW; ++i)
		if (following[i] == bObj)
		{
			following[i] = NULL;
		}
}
void Camera::addDrag(BaseObject *bObj, float amnt)
{
	for (int i = 0; i < MAX_DRAG; ++i)
		if (dragging[i] == NULL)
		{
			dragging[i] = bObj;
			dragAmnts[i] = amnt;
			return;
		}else if (dragging[i] == bObj)
		{
			return;
		}
}
void Camera::removeDrag(BaseObject *bObj)
{
	for (int i = 0; i < MAX_DRAG; ++i)
		if (dragging[i] == bObj)
		{
			dragging[i] = NULL;
			dragAmnts[i] = 0;
		}
}
void Camera::update(GameProperties *gp, float delta)
{
	Pos2 pos;
	int num_following = 0;
	for (int i = 0; i < MAX_FOLLOW; ++i)
		if (following[i] != NULL)
		{
			pos.add(following[i]->getPosition());
			++num_following;
		}
	if (num_following > 0)
	{
		camPos->set(gp->getRes());
		camPos->div(gp->getTileSize());
		camPos->mul(-.5);
		pos.mul(1.0f/(float)num_following);
		camPos->add(&pos);
		gp->setOffset(camPos);
	}
	for (int i = 0; i < MAX_DRAG; ++i)
		if (dragging[i] != NULL && dragAmnts[i] != 0)
		{
			dragging[i]->setOffset(camPos->getX()*dragAmnts[i], camPos->getY()*dragAmnts[i]);
		}
}