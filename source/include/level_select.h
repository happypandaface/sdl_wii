#ifndef _LEVEL_SELECT_H_
#define _LEVEL_SELECT_H_

class LevelSelect;

#include "game_properties.h"
#include "controller.h"

#define LS_MAX_LEVELS 2
#define LS_GOTO_WORLD_COUNT 2

class LevelSelect
{
	public:
		LevelSelect();
		~LevelSelect();
		void load(GameProperties *h);
		int draw(GameProperties *h, SDL_Surface *screen, float delta);
		int update(Controller *ctrl, GameProperties *h, float delta);
		int getSelection();
		void startSelecting();
	private:
		AnimationInstance *flyAround;
		AnimationInstance *gotoWorld;
		int goingToWorld;
		float gotoWorldCount;
		int curLevel;
		int selection;
		Pos2 levelPos[LS_MAX_LEVELS];
		Pos2 curPos;
};

#endif