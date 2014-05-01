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
#include "animation_holder.h"

#define TYP_CLIPS 1<<0
#define TYP_SOLID 1<<1
#define TYP_HITS 1<<2
#define TYP_DEAD 1<<3
#define TYP_HAS_GRAV 1<<4

class BaseObject
{
	public:
		BaseObject();
		virtual ~BaseObject();
		virtual int load(ResourceLoader *resLoader, AnimationHolder *animHolder);
		virtual int update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		virtual int each_object(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
		virtual int draw(ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen);
		virtual int doDraw(float x, float y, ResourceLoader *resLoader, GameProperties *gameProps, SDL_Surface *screen);//this is the one you want to override if you want multiple animations
		virtual void setPos(float x, float y);
		virtual int checkIfShouldBeRemoved();
		virtual void setToBeRemoved(int remove);
		virtual void setAnimation(Animation *a);
		virtual void doGravity(float strength, float delta);
		virtual Pos2 *getPosition();
		virtual int getLayer();
		virtual void setLayer(int l);
		virtual void die(BaseObject *killer);
		virtual void doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		virtual void setOffset(float x, float y);
		virtual void load_animations(AnimationHolder *animHolder);
		char getShoves();
		Pos2 *getSize();
		int checkHitDir(int hitDir);
		int checkType(long type);
		void addType(long type);
		void removeType(long type);
	protected:
		int shouldBeRemoved;
		char canShoves;
		Pos2 *pos;
		Pos2 *size;
		Pos2 *vel;
		Pos2 *offset;
		AnimationInstance *animInst;
		float speed;
		int hitDir;
		float restitution;
	private:
		int layer;
		long types;
};

#endif