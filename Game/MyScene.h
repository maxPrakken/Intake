#pragma once 

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "Button.h"
#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Upgrades.h"
#include "IEnemy.h"
#include "enemyBasic.h"
#include "Slider.h"

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

	void resetWorld();

private:

	void playerShoot();

	void addUpgrade(Upgrades upgrade, Vector2 position);
	void addEnemy(IEnemy::enemyTypes type, Vector2 position);
	void addStartEnemies();
	void addRandomUpgrades(double deltatime);
	void grabUpgrade();
	void deleteBullets();
	void buildPauseMenu();
	void destroyPauseMenu();
	void updatePauseMenu();
	void enemyShoot();
	void bulletHits();
	void deadEnemyCleanup();
	void playerDie();
	void healthHeartController();

	bool pausedMenuUp;
	bool paused;

	int wave;
	int score;

	float upgradeTimer = 0;
	float randomUpgradeTime = rand() % 20 + 10;

	std::vector<Entity*>pauseMenuVector;
	std::vector<Upgrade_Base*>upgradeVector;
	std::vector<Bullet*>bulletVector;
	std::vector<IEnemy*>enemyVector;
	std::vector<Bullet*>enemyBulletVector;
	
	Grid* background;
	Player* player;
	Entity* healthHearts;

	Button* button;

	EnemyBasic* enemy;
};
