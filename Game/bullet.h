#pragma once

#include <entity.h>

class Bullet : public Entity {
public:

	Bullet();
	Bullet(std::string texturepath);
	virtual ~Bullet();
	virtual void update(double deltatime);

	Vector2 direction;

	bool playerBullet = true;

	void setSpeed(float speed) { this->speed = speed; }

private:

	float speed;
};