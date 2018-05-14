#pragma once

#include "IEnemy.h"

class EnemyBasic : public IEnemy {

public:

	//default constructor
	EnemyBasic();
	//default deconstructor
	virtual ~EnemyBasic();
	//update function
	virtual void update(double deltatime);

	//shoot function
	virtual void shoot();

private:
	float shootTimer = 0;
	int randomMaxTimer = 1;
};