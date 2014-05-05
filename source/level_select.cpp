#include "level_select.h"
#include "res_loader.h"
#include <iostream>
#include "animation_holder.h"

LevelSelect::LevelSelect()
{
	curLevel = 0;
	selection = 0;
	goingToWorld = 0;
	gotoWorldCount = 0;
	flyAround = NULL;
	gotoWorld = NULL;
	levelPos[0].set(100, 100);
	levelPos[1].set(400, 200);
	curPos.set(&(levelPos[curLevel]));
}
LevelSelect::~LevelSelect()
{
	if (flyAround != NULL)
		delete flyAround;
}
void LevelSelect::startSelecting()
{
	gotoWorldCount = 0;
	goingToWorld = 0;
	selection = 0;
	if (gotoWorld != NULL)
		gotoWorld->reset();
}
int LevelSelect::getSelection()
{
	return selection;
}
void LevelSelect::load(GameProperties *gameProps)
{
	flyAround = new AnimationInstance(gameProps->getAnimHolder()->get_anim(ANIM_FLY_AROUND));
	gotoWorld = new AnimationInstance(gameProps->getAnimHolder()->get_anim(ANIM_GOTO_WORLD));
}

int LevelSelect::update(Controller *ctrl, GameProperties *gameProps, float delta)
{
	if (goingToWorld == 0)
	{
		if (flyAround != NULL)
			flyAround->update(delta);
		if (ctrl->eat_key(0, CTRL_LEFT))
			--curLevel;
		if (ctrl->eat_key(0, CTRL_RIGHT))
			++curLevel;
		if (ctrl->eat_key(0, CTRL_2))
			goingToWorld = 1;
		if (curLevel == -1)
			curLevel = LS_MAX_LEVELS-1;
		curLevel = curLevel%LS_MAX_LEVELS;
	}else if (goingToWorld == 1)
	{
		if (gotoWorld != NULL)
			gotoWorld->update(delta);
		gotoWorldCount += delta;
		if (gotoWorldCount > LS_GOTO_WORLD_COUNT)
			selection = curLevel+1;
	}
	return 1;
}

int LevelSelect::draw(GameProperties *gameProps, SDL_Surface *screen, float delta)
{
	gameProps->getResLoader()->draw_image(IMG_STARRY_BG, screen, 0, 0);
	gameProps->getResLoader()->draw_image(IMG_WORLD_1, screen, levelPos[0].getX(), levelPos[0].getY());
	gameProps->getResLoader()->draw_image(IMG_WORLD_2, screen, levelPos[1].getX(), levelPos[1].getY());
	Pos2 dst;
	dst.set(&(levelPos[curLevel]))->sub(&curPos);
	curPos.add(dst.mul(6*delta));
	if (flyAround != NULL && goingToWorld == 0)
		flyAround->draw(gameProps->getResLoader(), screen, curPos.getX(), curPos.getY()-32);
	else if (gotoWorld != NULL && goingToWorld == 1)
		gotoWorld->draw(gameProps->getResLoader(), screen, curPos.getX(), curPos.getY()-32);
	return 1;
}