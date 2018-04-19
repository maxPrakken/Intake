#pragma once

#include "../MXP3/include/entity.h"
#include <input.h>
#include "bullet.h"

class Player : public Entity {
public:

	//default constructor
	Player();
	//default deconstructor
	virtual ~Player();
	//update function
	virtual void update(double deltatime);

	//movement function
	void movement(double deltatime);

	Vector2 getVelocity() { return velocity; }

	int getHealth();
	float getBulletSpeed();

	bool canUp;
	bool canDown;
	bool canRight;
	bool canLeft;

	bool grounded;

	bool hasShot;

	Vector2 velocity;

	std::vector<Bullet*> getBullets() { return bullets; }

private:

	float speed;
	float bulletSpeed;
	int health;

	std::vector<Bullet*>bullets;
};