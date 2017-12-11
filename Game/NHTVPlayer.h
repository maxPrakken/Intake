#pragma once

#include "../MXP3/include/entity.h"
#include <input.h>
#include "bullet.h"

class NHTVScene;

class NHTVPlayer : public Entity {
public:

	//default constructor
	NHTVPlayer();
	//default deconstructor
	virtual ~NHTVPlayer();
	//update function
	virtual void update(double deltatime);

	//movement function
	void movement(double deltatime);
	//shoot function, fires a bullet
	void shoot();
	//deflect function, deflects bullets of the enemies
	void deflect();

	Vector2 getVelocity() { return velocity; }

	Vector2 getGravity() { return gravity; }

	int health;

	bool canUp;
	bool canDown;
	bool canRight;
	bool canLeft;

	bool grounded;

	Vector2 velocity;

	std::vector<Bullet*> getBullets() { return bullets; }

private:

	void bulletRotDir();

	float speed;

	Vector2 gravity;

	std::vector<Bullet*>bullets;
};