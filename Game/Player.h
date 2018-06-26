#pragma once

#include "../MXP3/include/agent.h"
#include <input.h>

class Player : public Agent {
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

	Vector2 canvasSize = Renderer::getInstance()->getResolution();
};
