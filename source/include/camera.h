#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera;

#include "game_properties.h"
#include "base_object.h"

#define MAX_FOLLOW 4
#define MAX_DRAG 4

class Camera
{
	public:
		Camera(GameProperties *gp, float distance);
		~Camera();
		void addFollow(BaseObject *bObj);
		void removeFollow(BaseObject *bObj);
		void clear();
		void addDrag(BaseObject *bObj, float amnt);
		void removeDrag(BaseObject *bObj);
		void update(GameProperties *gp, float delta);
	private:
		float distance;
		Pos2 *camPos;
		BaseObject *following[MAX_FOLLOW];
		BaseObject *dragging[MAX_DRAG];
		float dragAmnts[MAX_DRAG];
};

#endif