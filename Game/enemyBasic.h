#pragma once

#include "IEnemy.h"

class EnemyBasic : public IEnemy {

public:

	//default constructor
	EnemyBasic();
	//constructor with position build in, use this if you want to 
	//use the move functionality of the enemy
	EnemyBasic(Vector2 position, IEnemy::enemyTypes type);
	//default deconstructor
	virtual ~EnemyBasic();
	//update function
	virtual void update(double deltatime);

	//shoot function
	virtual void shoot();

private:
};
