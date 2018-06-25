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

	//returns the bullet direction in Vector2
	std::vector<Vector2> getBulletDirection(int bulletamount);

private:
	//the speed at which the bullet cirkel is rotating
	float circleSpeed = 0;
	//the starter angle for the bullet cirkel
	float circleAngle = 0;

	//Rounds Per Minute variable that defines how fast the boss enemy shoots
	double RPM;
	//timer for the RPM variable
	double RPMTimer;
};