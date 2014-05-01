#include "player.h"
#include "res_loader.h"
#include "animation_holder.h"
#include "giblet.h"
#include "player_indicator.h"
#include "blue_lazer.h"

Player::Player()
{
	addType(TYP_CLIPS);
	addType(TYP_HAS_GRAV);
	controller_num = 0;
	jumpVel = 8;
	jumpGlide = 18;
	setLayer(1);
	size->set(.5, .95);
	needs_indicator_make = 0;// set it when we get a player num
	dir_facing = DIR_RIGHT;// so that we have an initial direction
	released_suicide_button = 0;
	released_fire_button = 0;
	gun_cooldown = .2;
	ending_level = 0;// used to do the end level animation
	end_level_anim_time = 0;
}

void Player::endLevel(GameProperties* gameProps)
{
	pi->playerDied(this);
	ending_level = 1;
	end_level_anim_time = 0;
	if (dir_facing & DIR_RIGHT)
		setAnimation(gameProps->getAnimHolder(), ANIM_PLAYER_CUT_UP_RIGHT);
	if (dir_facing & DIR_LEFT)
		setAnimation(gameProps->getAnimHolder(), ANIM_PLAYER_CUT_UP_LEFT);
}

void Player::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder, ANIM_COOL_GUY_STAND_RIGHT);
}

void Player::setController(int num)
{
	needs_indicator_make = 1;// make an indicator on the next update
	controller_num = num;
}
void Player::die(BaseObject *killer)
{
	pi->playerDied(this);
	addType(TYP_DEAD);
	//pos->set(0, 0);
	//vel->set(0, 0);
}

void Player::doDeath(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	// add the giblets!
	for (int i = 0; i < 5; ++i)
	{
		Giblet *g1 = new Giblet();
		g1->load(gameProps->getResLoader(), gameProps->getAnimHolder());
		g1->setPos(pos->getX(), pos->getY());
		gameProps->addObject(g1);
	}
	gameProps->removePlayer();
	removeType(TYP_DEAD);
	gameProps->getCam()->removeFollow(this);
}

int Player::each_object(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, BaseObject *curr, float delta)
{
	Player *plr = dynamic_cast<Player*>(curr);
	if (plr != NULL)
	{
		float dist = getPosition()->dst(curr->getPosition());
		if (dist > 12)
		{
			die(this);
			curr->die(this);
		}
	}
	return 0;
}

int Player::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (ending_level == 1)
	{
		end_level_anim_time += delta;
	}else
	{
		if (needs_indicator_make)
		{
			needs_indicator_make = 0;
			pi = new PlayerIndicator(this, controller_num);
			pi->load(gameProps->getResLoader(), gameProps->getAnimHolder());
			gameProps->addObject(pi);
		}
		if (getPosition()->getY() > 7)
			die(NULL);
		if (contrlr->key_down(controller_num, CTRL_A))
		{
			if (released_suicide_button == 1)
				die(NULL);
		}else
			released_suicide_button = 1;
		int walking = 0;
		if (contrlr->key_down(controller_num, CTRL_LEFT))
		{
			walking = 1;
			vel->addX(-delta*speed);
			dir_facing = DIR_LEFT;
			if (cur_anim != ANIM_COOL_GUY_WALK_LEFT)
				setAnimation(gameProps->getAnimHolder(), ANIM_COOL_GUY_WALK_LEFT);
		}
		if (contrlr->key_down(controller_num, CTRL_RIGHT))
		{
			walking = 1;
			vel->addX(delta*speed);
			dir_facing = DIR_RIGHT;
			if (cur_anim != ANIM_COOL_GUY_WALK_RIGHT)
				setAnimation(gameProps->getAnimHolder(), ANIM_COOL_GUY_WALK_RIGHT);
		}
		if (walking == 0)
		{
			if (dir_facing & DIR_RIGHT && cur_anim != ANIM_COOL_GUY_STAND_RIGHT)
				setAnimation(gameProps->getAnimHolder(), ANIM_COOL_GUY_STAND_RIGHT);
			else
			if (dir_facing & DIR_LEFT && cur_anim != ANIM_COOL_GUY_STAND_LEFT)
				setAnimation(gameProps->getAnimHolder(), ANIM_COOL_GUY_STAND_LEFT);
		}
		
		if (contrlr->key_down(controller_num, CTRL_UP))
		{
			if (checkHitDir(DIR_DOWN))
			{
				vel->setY(-jumpVel);
			}else if (vel->getY() < 0)// only allow when going up
			{
				vel->addY(-jumpGlide*delta);
			}
		}
		//if (contrlr->key_down(controller_num, CTRL_DOWN))
		//	pos->addY(delta*speed);
		if (contrlr->key_down(controller_num, CTRL_2))
		{
			if (released_fire_button == 0 && cooldown <= 0)
			{
				released_fire_button = 1;
				cooldown = gun_cooldown;
				pos->addY(delta*speed);
				audioPlayer->playSound(SND_TONE);
				BlueLazer *bl = new BlueLazer();
				bl->load(gameProps->getResLoader(), gameProps->getAnimHolder());
				bl->setPos(pos->getX(), pos->getY());
				bl->setDirection(dir_facing);
				gameProps->addObject(bl);
			}
		}else
			released_fire_button = 0;
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}