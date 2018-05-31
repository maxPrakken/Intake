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

	bool hasShot;
	bool doubleShot = false;

	Vector2 velocity;

	int getMaxHealth() { return maxHealth; }

	void setRPM(double value) { RPM = value; }
	double getDefaultRPM() { return defaultRPM; }

	bool getDelete() { return deleteThis; }
	void setDelete(bool value) { deleteThis = value; }

private:

	float speed;
	float bulletSpeed;
	int maxHealth;

	bool deleteThis = false;

	double RPM;
	double defaultRPM;
	double RPMTimer;
};
