#pragma once 

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "Button.h"
#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Upgrades.h"
#include "IEnemy.h"

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

	void playerShoot();

	void addUpgrade(Upgrades upgrade, Vector2 position);
	void grabUpgrade();
	void deleteBullets();
	void buildPauseMenu();
	void destroyPauseMenu();
	void updatePauseMenu();


	bool pausedMenuUp = false;
	bool paused = false;

	std::vector<Entity*>pauseMenuVector;
	std::vector<Upgrade_Base*>upgradeVector;
	std::vector<Bullet*>bulletVector;
	
	Grid* background;
	Player* player;

	Button* button;
};