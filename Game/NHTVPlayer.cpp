#include "NHTVPlayer.h"

NHTVPlayer::NHTVPlayer()
{
	texturePath = "assets/INA.png";

	grounded = false;

	speed = 100;

	hasShot = false;

	velocity = Vector2(0, 0);
	gravity = Vector2(0, 200);
}

NHTVPlayer::~NHTVPlayer()
{

}

void NHTVPlayer::update(double deltatime)
{
	Entity::update(deltatime); 

	//std::cout << Input::getInstance()->getMouseToScreen().x << " " << Input::getInstance()->getMouseToScreen().y << std::endl;

	movement(deltatime);
	//bulletRotDir();	
}

void NHTVPlayer::movement(double deltatime)
{
	if (velocity.y < 500 && !grounded) {
		velocity += gravity * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_a)) {
		pos -= Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKey(SDLK_d)) {
		pos += Vector2(speed, 0) * deltatime;
	}

	if (Input::getInstance()->getKeyDown(SDLK_SPACE) && grounded) {
		velocity = Vector2(0, -500);
	}

	if (Input::getInstance()->getMouseButtonDown(1)) {
		hasShot = true;
		std::cout << "jk" << std::endl;
	}

	if (velocity.y != 0) {
		grounded = false;
	}

	pos += velocity * deltatime;
}

void NHTVPlayer::deflect()
{

}
