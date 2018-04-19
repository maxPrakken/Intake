#pragma once

#include "../MXP3/include/entity.h"

class IEnemy : public Entity {

public:
	int getHealth() { return health; }

	virtual void shoot() { }

	Vector2 direction;

private:
	int health;

	std::vector<Entity*>bullets;
};