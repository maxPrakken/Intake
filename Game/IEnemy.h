#pragma once

#include "../MXP3/include/agent.h"
#include "../MXP3/include/renderer.h"

class IEnemy : public Agent {

public:
	enum enemyTypes {
		BASIC,
		FAST,
		BOSS
	};

	IEnemy() {}
	virtual ~IEnemy() {}
	virtual void update(double deltatime);

	float getSpeed() { return speed; }
	void setSpeed(float speed) { this->speed = speed; }

	bool getIsDead() { return isDead; }

	virtual void shoot() { }
	Vector2 direction;

	//boolean canshoot
	bool canShoot;
	float shootTimer = 0;
	//start int, after first loop it gets randomized
	int randomMaxTimer = 1;

	int type;
	int pointsWorth;

	Vector2 startPosition;

	std::vector<Vector2> pointVector;

private:
	void goTo(double deltatime);
	void checkPoint();

	float speed = 70;

	int index = 0;
	int vectorIndex = 0;
	Vector2 point;

	bool isDead = false;

	std::vector<Entity*>bullets;
};