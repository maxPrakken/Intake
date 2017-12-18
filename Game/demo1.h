#pragma once

#include "../MXP3/include/scene.h"

#include "grid.h"

class Demo1 : public Scene{

public:
	//constructor 
	Demo1();
	//deconstructor
	virtual ~Demo1();
	//update function
	virtual void update(double deltatime);

private:


	Entity* hearts;

	Entity* finishDoor;

	Grid* background;

	void audioController();

	void hitEnemy();

	void enemyDie();

	void AI(double deltatime);

	void spawnEnemy(Vector2 position);

	void heartController();

	void goToNextLevel();

	void spawnWalls();

	void wallCollisionCheck();

	int enemiesAlive;

	double enemyHitTimer;
	bool enemyHitTimerCheck;
	float hitAfter;

	Entity* wallLeft;
	Entity* wallRight;
	Entity* wallTop;
	Entity* wallDown;

	std::vector<Entity*>wallVector;
};
