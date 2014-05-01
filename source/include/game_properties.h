#ifndef _GAME_PROPS_H_
#define _GAME_PROPS_H_

class GameProperties;

#include "pos2.h"
#include "camera.h"
#include "base_object.h"
#include "object_holder.h"
#include "animation_holder.h"
#include "res_loader.h"
#include "spawner.h"

#define MAX_PLAYERS 2

class GameProperties
{
	public:
		GameProperties();
		~GameProperties();
		Pos2 *getOffset();
		void setOffset(Pos2 *os);
		Pos2 *addOffset(float x, float y);
		Pos2 *getTileSize();
		Pos2 *getRes();
		Pos2 *setTileSize(float x, float y);
		Camera *getCam();
		void addObject(BaseObject *obj);
		void addObjsTo(ObjectHolder *obj);
		ResourceLoader *getResLoader();
		AnimationHolder *getAnimHolder();
		void removePlayer();
		int getPlayersLeft();
		void addPlayer();
		void setActiveSpawn(Spawner *s);
		Pos2 *getSpawnPos();
	private:
		Spawner *activeSpawn;
		int players;
		ResourceLoader *resLoader;
		AnimationHolder *animHolder;
		Camera *cam;
		ObjectHolder *objsToAdd;
		Pos2 *offset;
		Pos2 *tileSize;
		Pos2 *res;
};

#endif