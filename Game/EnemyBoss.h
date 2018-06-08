#pragma once

#include "IEnemy.h"

class EnemyBoss : public IEnemy {
public:
	//default constructor
	EnemyBoss();
	//deconstructor
	virtual ~EnemyBoss();
	//update function
	virtual void update(double deltatime);

	//shoot overloader
	virtual void shoot();

	std::vector<Vector2> getBulletDirection(int bulletamount);

private:

	float circleSpeed = 0;
	float circleAngle = 0;

	double RPM;
	double RPMTimer;
};