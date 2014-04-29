#include "game_properties.h"

GameProperties::GameProperties()
{
	offset = new Pos2();
	tileSize = new Pos2();
	cam = new Camera(this, 1);
	res = new Pos2(640, 480);
	objsToAdd = new ObjectHolder();
	resLoader = new ResourceLoader();
	animHolder = new AnimationHolder();
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