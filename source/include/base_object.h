#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

class BaseObject;

#include "SDL/SDL.h"
#include "pos2.h"
#include "controller.h"
#include "res_loader.h"
#include "game_properties.h"
#include "audio.h"
#include "animation.h"
#include "object_holder.h"

#define TYP_CLIPS 1<<0
#define TYP_SOLID 1<<1
#define TYP_HITS 1<<2

#define DIR_DOWN 1<<0
#define DIR_RIGHT 1<<1
#define DIR_LEFT 1<<2
#define DIR_UP 1<<3

class BaseObject
{
	public:
		BaseObject();
		virtual ~BaseObject();
		virtual int load(ResourceLoader *resLoader);
		virtual int update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		virtual int draw(ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen);
		virtual void setPos(float x, float y);
		virtual int checkIfShouldBeRemoved();
		virtual void setToBeRemoved(int remove);
		virtual void setAnimation(Animation *a);
		virtual void doGravity(float strength, float delta);
		virtual Pos2 *getPosition();
		int checkHitDir(int hitDir);
		int checkType(long type);
		void addType(long type);
		void removeType(long type);
	protected:
		int shouldBeRemoved;
		Pos2 *pos;
		Pos2 *size;
		Pos2 *vel;
		AnimationInstance *animInst;
		float speed;
		int hitDir;
		float restitution;
	private:
		long types;
};

#endif