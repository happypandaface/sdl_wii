#ifndef _PLAYER_H
#define _PLAYER_H

class Player;

#include "SDL/SDL.h"
#include "pos2.h"
#include "controller.h"
#include "res_loader.h"
#include "game_properties.h"
#include "base_object.h"

class Player : public BaseObject
{
	public:
		Player();
		~Player();
		void setController(int num);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
	private:
		int controller_num;
		float jumpVel;
		float jumpGlide;
};
#endif