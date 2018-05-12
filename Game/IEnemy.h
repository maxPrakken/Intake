#pragma once

#include "../MXP3/include/entity.h"

class IEnemy : public Entity {

public:
	enum enemyTypes {
		BASIC,
		BASIC2,
		BOSS
	};

	IEnemy() {}
	virtual ~IEnemy() {}
	virtual void update(double deltatime) { Entity::update(deltatime); }

	int getHealth() { return health; }

	virtual void shoot() { }
	Vector2 direction;

private:
	int health;

	std::vector<Entity*>bullets;
};