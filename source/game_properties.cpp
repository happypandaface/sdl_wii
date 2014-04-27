#include "game_properties.h"

GameProperties::GameProperties()
{
	offset = new Pos2();
	tileSize = new Pos2();
}

GameProperties::~GameProperties()
{
	delete offset;
}

Pos2 *GameProperties::getOffset()
{
	return offset;
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
}