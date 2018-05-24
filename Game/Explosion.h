#pragma once

#include "../MXP3/include/entity.h"

class Explosion : public Entity {
public:
	
	Explosion();
	Explosion(Vector2 position, Vector2 size);
	virtual ~Explosion();
	virtual void update(double deltatime);

	bool getExplosionDone() { return explosionDone; }

private:
	bool explosionDone = false;
};
