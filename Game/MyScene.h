#pragma once 

#include "../MXP3/include/scene.h"

#include <sceneManager.h>
#include <mathM.h>
#include <fstream>
#include <algorithm>
#include <iostream>

#include "Button.h"
#include "Grid.h"
#include "Player.h"
#include "Bullet.h"
#include "Upgrades.h"
#include "IEnemy.h"
#include "EnemyBasic.h"
#include "EnemyFast.h"
#include "EnemyBoss.h"
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

	EnemyBoss* boss;

private:

	void playerShoot();

	void addUpgrade(Upgrades upgrade, Vector2 position);
	void addEnemy(IEnemy::enemyTypes type, Vector2 position);
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
	void addZLayers(int zlayerAmount);
	void displayHighScore();

	void saveHighScore(std::vector<int> strs);
	void checkHighScore();

	void levelBuilder();
	void levelManager();

	bool pausedMenuUp;
	bool pausedMenuBuild = false;
	bool paused;

	int wave = 1;
	int level = 1;
	int score = 0;	

	bool checkHighScoreOnce = false;

	float upgradeTimer = 0;
	float randomUpgradeTime = rand() % 5 + 4;

	std::vector<Entity*>pauseMenuVector;
	std::vector<Upgrade_Base*>upgradeVector;
	std::vector<Bullet*>bulletVector;
	std::vector<IEnemy*>enemyVector;
	std::vector<Explosion*>explosionVector;
	
	Grid* background;
	Player* player;
	
	SDL_Rect Message_rect{
		Message_rect.x = 450,
		Message_rect.y = 0,
		Message_rect.w = 100,
		Message_rect.h = 100
	};

	Button* button;

	EnemyBasic* enemy;
};
