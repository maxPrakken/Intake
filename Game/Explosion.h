#pragma once

#include "../MXP3/include/entity.h"

class Explosion : public Entity {
public:
	//default constructor
	Explosion();
	//constructor overloader that sets position and size
	Explosion(Vector2 position, Vector2 size);
	//deconstructor
	virtual ~Explosion();
	//update function that takes deltatime double variable
	virtual void update(double deltatime);

	//gets boolean explosiondone 
	bool getExplosionDone() { return explosionDone; }

private:
	//private boolean explosiondone, true if the animation is over
	bool explosionDone = false;
};
