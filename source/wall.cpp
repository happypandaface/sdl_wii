#include "wall.h"

Wall::Wall()
{
	addType(TYP_SOLID);
}

Wall::~Wall()
{
}

/*
int Wall::load(ResourceLoader *resLoader)
{
	spriteImage = resLoader->get_image(IMG_DIRT_SQUARE);
	//spriteImage = resLoader->get_image(IMG_TEST);
	return 1;
}*/