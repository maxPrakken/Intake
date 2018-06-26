#pragma once

#include <entity.h>
#include <typeinfo>

#include "IEnemy.h"
#include "Player.h"

#include "../MXP3/include/agent.h"

class Bullet : public Entity {
public:
	//basic contstructor
	Bullet();
	//constructor with texturepath to set bullet sprite
	Bullet(std::string texturepath);
	//constructor with texturepath to set bullet sprite, and origin
	//so bullet doesnt hit the original shooter
	Bullet(std::string texturepath, Entity* origin);
	//deconstructor
	virtual ~Bullet();
	//update function, takes deltatime double
	virtual void update(double deltatime);

	//direction the bullet is flying in
	Vector2 direction;

	//if the bullet is originaly shot by the player
	bool playerBullet = true;

	//sets the private speed variable that controlls the bullet speed
	void setSpeed(float speed) { this->speed = speed; }
	//sets the private origin variable in case you did't use the constructor overloader
	void setOrigin(Entity* origin) { this->origin = origin; }

	//gets the isdead boolean
	bool getIsDead() { return isDead; }

private:
	void hit();

	//sets origin type, makes sure you dont hit your own
	Entity* origin;

	//boolean that checks if the bullet is dead
	bool isDead = false;

	//private float speed, that controlls the bullet speed
	float speed;
	//private int damage that says how much damage a bullet does on impact with a agent.
	int damage;
};