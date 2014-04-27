#include "player.h"
#include "res_loader.h"

Player::Player()
{
	addType(TYP_CLIPS);
	controller_num = 0;
	jumpVel = 8;
	jumpGlide = 18;
}

Player::~Player()
{
}

void Player::setController(int num)
{
	controller_num = num;
}

int Player::update(ObjectHolder *objHolder, GameProperties *gameProps, AudioPlayer *audioPlayer, Controller *contrlr, float delta)
{
	if (contrlr->key_down(controller_num, CTRL_LEFT))
		vel->addX(-delta*speed);
	if (contrlr->key_down(controller_num, CTRL_RIGHT))
		vel->addX(delta*speed);
	if (contrlr->key_down(controller_num, CTRL_UP))
		if (checkHitDir(DIR_DOWN))
			vel->setY(-jumpVel);
		else if (vel->getY() < 0)// only allow when going up
			vel->addY(-jumpGlide*delta);
	//if (contrlr->key_down(controller_num, CTRL_DOWN))
	//	pos->addY(delta*speed);
	if (contrlr->key_down(controller_num, CTRL_2))
	{
		pos->addY(delta*speed);
		audioPlayer->playSound(SND_TONE);
	}
	return BaseObject::update(objHolder, gameProps, audioPlayer, contrlr, delta);
}