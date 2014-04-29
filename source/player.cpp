#include "player.h"
#include "res_loader.h"
#include "animation_holder.h"
#include "giblet.h"

Player::Player()
{
	addType(TYP_CLIPS);
	addType(TYP_HAS_GRAV);
	controller_num = 0;
	jumpVel = 8;
	jumpGlide = 18;
	size->set(.5, 1);
}

Player::~Player()
{
}

void Player::load_animations(AnimationHolder *animHolder)
{
	setAnimation(animHolder->get_anim(ANIM_COOL_GUY_WALK));
}

void Player::setController(int num)
{
	controller_num = num;
}
void Player::die(BaseObject *killer)
{
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
	removeType(TYP_DEAD);
	gameProps->getCam()->removeFollow(this);
}

int Player::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (contrlr->key_down(controller_num, CTRL_LEFT))
		vel->addX(-delta*speed);
	if (contrlr->key_down(controller_num, CTRL_RIGHT))
		vel->addX(delta*speed);
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
		pos->addY(delta*speed);
		audioPlayer->playSound(SND_TONE);
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}