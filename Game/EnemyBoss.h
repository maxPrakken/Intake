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

private:
	int test = 0;
};