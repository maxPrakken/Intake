#pragma once

#include "IEnemy.h"

class EnemyBasic2 : public IEnemy {

public:

	//default constructor
	EnemyBasic2();
	//constructor with position build in, use this if you want to 
	//use the move functionality of the enemy
	EnemyBasic2(Vector2 position);
	//default deconstructor
	virtual ~EnemyBasic2();
	//update function
	virtual void update(double deltatime);

	virtual void shoot();

private:
	
};