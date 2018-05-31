#pragma once 

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "Button.h"
#include "Grid.h"
#include "Player.h"
#include "Bullet.h"
#include "Upgrades.h"
#include "IEnemy.h"
#include "EnemyBasic.h"
#include "EnemyFast.h"
#include "Slider.h"
#include "Explosion.h"
#include "HealthHearts.h"

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
	//constructor with custom amount of zlayers
	MyScene(int ZLayer_amount);
	//deconstructor
	virtual ~MyScene();
	//update function
	virtual void update(double deltatime);

	void resetWorld();

	HealthHearts* healthHearts;

private:

	void playerShoot();

	void addUpgrade(Upgrades upgrade, Vector2 position);
	void addEnemy(IEnemy::enemyTypes type, Vector2 position);
	void addStartEnemies();
	void addRandomUpgrades(double deltatime);
	void grabUpgrade();
	void deleteBullets();
	void deleteExplosions();
	void buildPauseMenu();
	void destroyPauseMenu();
	void updatePauseMenu();
	void enemyShoot();
	void bulletHits();
	void deadEnemyCleanup();
	void playerDie();
	void healthHeartController();
	void addZLayers(int zlayerAmount);

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
	std::vector<Explosion*>explosionVector;
	
	Grid* background;
	Player* player;
	

	Button* button;

	EnemyBasic* enemy;
};
