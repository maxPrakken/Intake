#pragma once 

#include "../MXP3/include/scene.h"

#include "grid.h"
#include "Player.h"
#include "bullet.h"

class MyScene : public Scene {
public:

	//constuctor
	MyScene();
	//deconstructor
	virtual ~MyScene();
	//update function
	virtual void update(double deltatime);

private:

	void EntitiesGrounded();

	void platformSpawn(Vector2 position);

	void addBulletsToScene();

	void playerShoot();

	std::vector<Entity*>platformVector;

	Grid* background;
	Player* player;
};