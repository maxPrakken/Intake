#pragma once

#include "IEnemy.h"

class EnemyBasic : public Entity {

public:

	//default constructor
	EnemyBasic();
	//default deconstructor
	virtual ~EnemyBasic();
	//update function
	virtual void update(double deltatime);

private:
	
};