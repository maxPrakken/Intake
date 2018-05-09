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

	virtual void shoot();

private:
	
};