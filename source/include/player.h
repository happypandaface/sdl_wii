#ifndef _PLAYER_H
#define _PLAYER_H

class Player;

#include "SDL/SDL.h"
#include "pos2.h"
#include "controller.h"
#include "res_loader.h"
#include "game_properties.h"
#include "base_object.h"
#include "animation_holder.h"
#include "player_indicator.h"
#include "guy.h"

class Player : public Guy
{
	public:
		Player();
		void setController(int num);
		void die(BaseObject *killer);
		void load_animations(AnimationHolder *animHolder);
		int update(ObjectHolder *objHolder, GameProperties *gameProps,  AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		int each_object(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta);
		void doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta);
		void endLevel(GameProperties* gameProps);
	private:
		int ending_level;
		float end_level_anim_time;
		int released_suicide_button;
		int released_fire_button;
		float gun_cooldown;
		int controller_num;
		int needs_indicator_make;
		float jumpVel;
		float jumpGlide;
		PlayerIndicator *pi;
};
#endif