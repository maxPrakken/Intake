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
	//std::vector<Vector2>vector2Vector;
private:
	
};