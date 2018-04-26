#pragma once 

#include "../MXP3/include/scene.h"

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Upgrades.h"

#include <typeinfo>
#include <iostream>

class MyScene : public Scene {
public:
	enum Upgrades
	{
		HEALTH,
		RPM,
		DOUBLESHOT
	};

	//constuctor
	MyScene();
	//deconstructor
	virtual ~MyScene();
	//update function
	virtual void update(double deltatime);

private:

	void addBulletsToScene();

	void playerShoot();

	void addUpgrade(Upgrades upgrade, Vector2 position);
	void grabUpgrade();

	std::vector<Upgrade_Base*>upgradeVector;
	
	Grid* background;
	Player* player;
};