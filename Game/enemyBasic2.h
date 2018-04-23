#pragma once

#include "EnemyBasic.h"

class EnemyBasic2 : public EnemyBasic {

public:

	//default constructor
	EnemyBasic2();
	//default deconstructor
	virtual ~EnemyBasic2();
	//update function
	virtual void update(double deltatime);

	virtual void shoot();

private:
	
};