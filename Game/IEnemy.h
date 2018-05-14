#pragma once

#include "../MXP3/include/entity.h"

class IEnemy : public Entity {

public:
	enum enemyTypes {
		BASIC,
		BASIC2,
		BOSS
	};

	IEnemy() {}
	virtual ~IEnemy() {}
	virtual void update(double deltatime);

	int getHealth() { return health; }
	void setHealth(int health) { this->health = health; }

	virtual void shoot() { }
	Vector2 direction;

	//boolean canshoot
	bool canShoot;

	Vector2 startPosition;

	std::vector<Vector2> pointVector;

private:
	void goTo(double deltatime);
	void checkPoint();

	int health;
	float speed = 70;

	int index = 0;
	int vectorIndex = 0;
	Vector2 point;

	std::vector<Entity*>bullets;
};