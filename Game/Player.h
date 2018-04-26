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

	int health;

	float getBulletSpeed();

	bool canUp;
	bool canDown;
	bool canRight;
	bool canLeft;

	bool hasShot;

	Vector2 velocity;

	std::vector<Bullet*> getBullets() { return bullets; }

private:

	float speed;
	float bulletSpeed;
	int maxHealth;

	std::vector<Bullet*>bullets;
};