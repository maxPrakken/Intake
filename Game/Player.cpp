#include "Player.h"

Player::Player()
{
	spitesheetPath = "assets/spritesheets/player_concept2_spritesheet.png";
	animator.rows = Vector2(4, 1);
	animator.paused = true;
	animator.cur = 0;
	animator.animateFromTo = Vector2(1, 3);
	animator.switchAfter = 0.1f;
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

	if (health <= 0) {
		animator.paused = false;
		if (animator.cur == animator.rows.x - 1) {
			animator.paused = true;
			deleteThis = true;
		}
	}
	if (health > maxHealth) {
		health = maxHealth;
	}
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
