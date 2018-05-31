#pragma once

#include <entity.h>
#include "IEnemy.h"
#include "Player.h"

#include "../MXP3/include/agent.h"

class Bullet : public Entity {
public:

	Bullet();
	Bullet(std::string texturepath);
	Bullet(std::string texturepath, Entity* origin);
	virtual ~Bullet();
	virtual void update(double deltatime);

	Vector2 direction;

	bool playerBullet = true;

	void setSpeed(float speed) { this->speed = speed; }
	void setOrigin(Entity* origin) { this->origin = origin; }

private:
	void hit();

	//sets origin type, makes sure you dont hit your own
	Entity* origin;

	float speed;
	int damage;
};