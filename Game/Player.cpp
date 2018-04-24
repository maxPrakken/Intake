#include "Player.h"

Player::Player()
{
	texturePath = "assets/player_concept2.png";

	grounded = false;

	speed = 200;
	bulletSpeed = -10;

	hasShot = false;

	velocity = Vector2(0, 0);
}

Player::~Player()
{

}

void Player::update(double deltatime)
{
	Entity::update(deltatime); 

	movement(deltatime);
}

void Player::movement(double deltatime)
{
	if (Input::getInstance()->getKey(SDLK_w)) {
		pos -= Vector2(0, speed) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_a)) {
		pos -= Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_s)) {
		pos += Vector2(0, speed) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_d)) {
		pos += Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKeyDown(SDLK_SPACE)) {
		hasShot = true;
		Audio::getInstance()->playAudio("pewSound.wav", 0, 1);
	}

	pos += velocity * deltatime;
}

int Player::getHealth(){
	return health;
}

float Player::getBulletSpeed()
{
	return bulletSpeed;
}
