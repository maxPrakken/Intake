#include "Player.h"

Player::Player()
{
	texturePath = "assets/player_concept2.png";

	speed = 200;
	bulletSpeed = -10;
	hasShot = false;

	health = 3;
	maxHealth = health;
	velocity = Vector2(0, 0);
}

Player::~Player()
{
	for (unsigned int i = 0; i < bullets.size(); i++) {
		removechild(bullets[i]);
		delete bullets[i];
	}
	bullets.clear();
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

float Player::getBulletSpeed()
{
	return bulletSpeed;
}
