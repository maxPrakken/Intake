#pragma once

#include "IEnemy.h"

class EnemyFast : public IEnemy {

public:
	//default constructor
	EnemyFast();
	//constructor with position build in, use this if you want to 
	//use the move functionality of the enemy
	EnemyFast(Vector2 position);
	//default deconstructor
	virtual ~EnemyFast();
	//update function
	virtual void update(double deltatime);

	//shoot function
	virtual void shoot();

private:

};