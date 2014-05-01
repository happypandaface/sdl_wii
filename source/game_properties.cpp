#include "game_properties.h"
#include "spawner.h"

GameProperties::GameProperties()
{
	offset = new Pos2();
	tileSize = new Pos2();
	cam = new Camera(this, 1);
	res = new Pos2(640, 480);
	objsToAdd = new ObjectHolder();
	resLoader = new ResourceLoader();
	animHolder = new AnimationHolder();
	players = 0;
	activeSpawn = NULL;
}

GameProperties::~GameProperties()
{
	delete offset;
	delete tileSize;
	delete res;
	delete cam;
	delete objsToAdd;
	delete resLoader;
	delete animHolder;
}

void GameProperties::setActiveSpawn(Spawner *s)
{
	if (activeSpawn != NULL)
		activeSpawn->setInactive();
	activeSpawn = s;
	activeSpawn->setActive();
}
Pos2 *GameProperties::getSpawnPos()
{
	if (activeSpawn == NULL)
		return NULL;
	return activeSpawn->getSpawnPos();
}

void GameProperties::removePlayer()
{
	//for (int i = 0; i < MAX_PLAYERS; ++i)
	//	if (players[i] == p)
	//		players[i] = NULL;
	--players;
}
int GameProperties::getPlayersLeft()
{
	//int left = 0;
	//for (int i = 0; i < MAX_PLAYERS; ++i)
	//	if (players[i] != NULL)
	//		left++;
	//return left;
	return players;
}
void GameProperties::addPlayer(/*Player *p*/)
{
	//for (int i = 0; i < MAX_PLAYERS; ++i)
	//	if (players[i] == NULL)
	//		players[i] = p;
	++players;
}

ResourceLoader *GameProperties::getResLoader()
{
	return resLoader;
}
AnimationHolder *GameProperties::getAnimHolder()
{
	return animHolder;
}

void GameProperties::addObjsTo(ObjectHolder *objs)
{
	ObjectIterator *objIter = objsToAdd->getIterator();
	BaseObject *curr;
	while(objsToAdd->hasNext(objIter))
	{
		curr = objsToAdd->next(objIter);
		objs->addObject(curr);
	}
	objsToAdd->clear();
	objsToAdd->destroyIterator(objIter);
}
void GameProperties::addObject(BaseObject *obj)
{
	objsToAdd->addObject(obj);
}

Pos2 *GameProperties::getOffset()
{
	return offset;
}

Camera *GameProperties::getCam()
{
	return cam;
}

Pos2 *GameProperties::getRes()
{
	return res;
}

void GameProperties::setOffset(Pos2 *os)
{
	offset->set(os);
}

Pos2 *GameProperties::addOffset(float x, float y)
{
	offset->addX(x);
	offset->addY(y);
	return getOffset();
}

Pos2 *GameProperties::getTileSize()
{
	return tileSize;
}
Pos2 *GameProperties::setTileSize(float x, float y)
{
	tileSize->setX(x);
	tileSize->setY(y);
	return tileSize;
}