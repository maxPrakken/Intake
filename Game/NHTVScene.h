#pragma once 

#include "../MXP3/include/scene.h"

#include "grid.h"
#include "NHTVPlayer.h"
#include "bullet.h"

class NHTVScene : public Scene {
public:

	//constuctor
	NHTVScene();
	//deconstructor
	virtual ~NHTVScene();
	//update function
	virtual void update(double deltatime);

private:

	void EntitiesGrounded();

	void platformSpawn(Vector2 position);

	void addBulletsToScene();

	std::vector<Entity*>platformVector;

	Grid* background;
	NHTVPlayer* player;
};