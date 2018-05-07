#include "Player.h"

Player::Player()
{
	texturePath = "assets/player_concept2.png";
	size = Vector2(50, 50);

	speed = 200;
	bulletSpeed = -10;
	hasShot = false;

	health = 3;
	maxHealth = health;
	velocity = Vector2(0, 0);

	defaultRPM = 250;
	RPM = defaultRPM;
	RPMTimer = 0;
}

Player::~Player()
{

}

void Player::update(double deltatime)
{
	Entity::update(deltatime); 

	RPMTimer += deltatime; 
	
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

	if (Input::getInstance()->getKey(SDLK_SPACE)) {
		//go from seconds to RPM(rounds per minute)
		double xValue = RPM / 60;
		double fireTime = 1 / xValue;
		if (RPMTimer > fireTime) {

			hasShot = true;
			RPMTimer = 0;
			Audio::getInstance()->playAudio("pewSound.wav", 0, 1);
		}
	}

	pos += velocity * deltatime;
}

float Player::getBulletSpeed()
{
	return bulletSpeed;
}
