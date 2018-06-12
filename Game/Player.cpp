#include "Player.h"

Player::Player()
{
	texturePath = "assets/player_concept2.png";
	size = Vector2(50, 50);

	health = 5;
	maxHealth = health;

	speed = 200;
	bulletSpeed = -10;
	hasShot = false;

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

	if (health > maxHealth) {
		health = maxHealth;
	}
}

void Player::movement(double deltatime)
{
	if (Input::getInstance()->getKey(SDLK_w) && pos.y > 0) {
		pos -= Vector2(0, speed) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_a) && pos.x > 0) {
		pos -= Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_s) && pos.y < (canvasSize.y - size.y)) {
		pos += Vector2(0, speed) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_d) && pos.x < (canvasSize.x - size.x)) {
		pos += Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_SPACE)) {
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
