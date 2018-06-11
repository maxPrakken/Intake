#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	player = new Player();
	addchild(player);

	healthHearts = new HealthHearts(player);
	healthHearts->setZLayer(1);
	addchild(healthHearts);

	paused = false;
	pausedMenuUp = false;
}

MyScene::MyScene(int ZLayer_amount)
{
	addZLayers(ZLayer_amount);	

	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	player = new Player();
	player->setZLayer(1);
	addchild(player);

	healthHearts = new HealthHearts(player);
	healthHearts->setZLayer(2);
	addchild(healthHearts);

	paused = false;
	pausedMenuUp = false;

	wave = 0;
	score = 0;
}

MyScene::~MyScene()
{
	//clears upgradeVector
	std::vector<Upgrade_Base*>::iterator it = upgradeVector.begin();
	while (it != upgradeVector.end()) {
		Upgrade_Base* u = (*it);
		it = upgradeVector.erase(it);
		this->removechild(u);
	}
	upgradeVector.clear();

	//clears pauseMenuVector
	std::vector<Entity*>::iterator that = pauseMenuVector.begin();
	while (that != pauseMenuVector.end()) {
		Entity* u = (*that);
		that = pauseMenuVector.erase(that);
		this->removechild(u);
	}
	pauseMenuVector.clear();

	//clears explosionVector
	std::vector<Explosion*>::iterator that2 = explosionVector.begin();
	while (that2 != explosionVector.end()) {
		Explosion* u = (*that2);
		that2 = explosionVector.erase(that2);
		this->removechild(u);
	}
	pauseMenuVector.clear();

	//clears bulletVector
	std::vector<Bullet*>::iterator those = bulletVector.begin();
	while (those != bulletVector.end()) {
		Bullet* u = (*those);
		those = bulletVector.erase(those);
		this->removechild(u);
	}
	bulletVector.clear();

	//clears enemyVector
	std::vector<IEnemy*>::iterator those2 = enemyVector.begin();
	while (those2 != enemyVector.end()) {
		IEnemy* u = (*those2);
		those2 = enemyVector.erase(those2);
		this->removechild(u);
	}
	enemyVector.clear();

	if (background != NULL) {
		delete background;
		background = NULL;
	}

	if (player != NULL) {
		delete player;
		player = NULL;
	}
}

void MyScene::update(double deltatime)
{
	if (Input::getInstance()->getKeyDown(SDLK_e)) {
		levelBuilder();
	}
	if (Input::getInstance()->getKeyDown(SDLK_r)) {
		addUpgrade(Upgrades::RPM, Vector2(300, 500));
	}
	if (Input::getInstance()->getKeyDown(SDLK_t)) {
		addUpgrade(Upgrades::DOUBLESHOT, Vector2(300, 500));
	}
	if (Input::getInstance()->getKeyDown(SDLK_y)) {
		addUpgrade(Upgrades::HEALTH, Vector2(300, 500));
	}

	if (!paused) {
		Scene::update(deltatime);

		if (pausedMenuUp) {
			destroyPauseMenu();
			pausedMenuUp = false;
			pausedMenuBuild = false;
		}
		
		addRandomUpgrades(deltatime);
	}
	else {
		if (!pausedMenuBuild) {
			buildPauseMenu();
			pausedMenuBuild = true;
		}
		updatePauseMenu();
	}

	//pauses the entire scene, nothing gets updated
	if (Input::getInstance()->getKeyDown(SDLK_ESCAPE)) {
		if (paused) {
			paused = false;
			pausedMenuUp = true;
			return;
		}
		paused = true;
	}

	if (player->hasShot) {
		playerShoot();
	}

	grabUpgrade();
	deleteBullets();
	enemyShoot();
	bulletHits();
	deadEnemyCleanup();
	playerDie();
	deleteExplosions();
	levelManager();
}

void MyScene::resetWorld()
{
	std::vector<IEnemy*>::iterator those2 = enemyVector.begin();
	while (those2 != enemyVector.end()) {
		IEnemy* u = (*those2);
		those2 = enemyVector.erase(those2);
		this->removechild(u);
	}
	enemyVector.clear();

	//clears upgradeVector
	std::vector<Upgrade_Base*>::iterator it = upgradeVector.begin();
	while (it != upgradeVector.end()) {
		Upgrade_Base* u = (*it);
		it = upgradeVector.erase(it);
		this->removechild(u);
	}
	upgradeVector.clear();

	//clears bulletvector
	std::vector<Bullet*>::iterator it2 = bulletVector.begin();
	while (it2 != bulletVector.end()) {
		Bullet* u = (*it2);
		it2 = bulletVector.erase(it2);
		this->removechild(u);
	}
	bulletVector.clear();

	if (player->health <= 0) {
		player = new Player();
		this->addchild(player);
		player->health = player->getMaxHealth();
	}
	
	paused = false;
	pausedMenuUp = true;

	levelBuilder();

	wave = 1;
	score = 0;
}

void MyScene::playerShoot()
{
	Bullet* bullet = new Bullet();
	bullet->setOrigin(player);
	bullet->pos = player->pos;
	bullet->pos.y = player->pos.y - player->size.y / 2 + 30;

	Bullet* bullet2 = new Bullet();
	bullet2->setOrigin(player);
	bullet2->pos = player->pos;
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 40;
	bullet2->pos.x = player->pos.x + player->size.x - 12;

	bullet->direction = Vector2(0, player->getBulletSpeed());

	bullet2->direction = Vector2(0, player->getBulletSpeed());

	bulletVector.push_back(bullet);
	bulletVector.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

	if (player->doubleShot) {
		Bullet* bullet3 = new Bullet();
		bullet3->setOrigin(player);
		bullet3->pos = player->pos;
		bullet3->pos.x = player->pos.x + 10;
		bullet3->pos.y = player->pos.y - player->size.y / 2 + 31;

		Bullet* bullet4 = new Bullet();
		bullet4->setOrigin(player);
		bullet4->pos = player->pos;
		bullet4->pos.y = player->pos.y - player->size.y / 2 + 34;
		bullet4->pos.x = player->pos.x + player->size.x - 22;

		bullet3->direction = Vector2(0, player->getBulletSpeed());

		bullet4->direction = Vector2(0, player->getBulletSpeed());

		bulletVector.push_back(bullet3);
		bulletVector.push_back(bullet4);

		addchild(bullet3);
		addchild(bullet4);
	}

	player->hasShot = false;
}

void MyScene::addUpgrade(Upgrades upgrade, Vector2 position)
{
	switch (upgrade)
	{
		case HEALTH:
		{
			Health_Upgrade * healthupgrade = new Health_Upgrade();
			healthupgrade->pos = position;
			addchild(healthupgrade);
			upgradeVector.push_back(healthupgrade);
			break;
		}
		case RPM:
		{
			RPM_Upgrade * rpmupgrade = new RPM_Upgrade();
			rpmupgrade->pos = position;
			addchild(rpmupgrade);
			upgradeVector.push_back(rpmupgrade);
			break;
		}
		case DOUBLESHOT:
		{
			DoubleShot_Upgrade* doubleshot = new DoubleShot_Upgrade();
			doubleshot->pos = position;
			addchild(doubleshot);
			upgradeVector.push_back(doubleshot);
			break;
		}
		default:
		{
			std::cout << "the enum you entered is not a valid upgrade enum value" << std::endl;
			break;
		}
	}
}

void MyScene::addEnemy(IEnemy::enemyTypes type, Vector2 position)
{
	switch (type)
	{
		case IEnemy::BASIC:
		{
			EnemyBasic* enemy = new EnemyBasic(position);
			addchild(enemy);
			enemyVector.push_back(enemy);
			break;
		}

		case IEnemy::FAST:
		{
			EnemyFast* enemy = new EnemyFast(position);
			enemyVector.push_back(enemy);
			addchild(enemy);
			break;
		}

		case IEnemy::BOSS:
		{
			EnemyBoss* boss = new EnemyBoss();
			enemyVector.push_back(boss);
			addchild(boss);
			break;
		}

		default:
		{
			break;
		}
	}
}

void MyScene::addStartEnemies()
{
	addEnemy(IEnemy::BASIC, Vector2(200, 150));
	addEnemy(IEnemy::BOSS, Vector2(0, 0));
	//addEnemy(IEnemy::BASIC, Vector2(360, 50));
	//addEnemy(IEnemy::FAST, Vector2(440, 50));
}

void MyScene::addRandomUpgrades(double deltatime)
{
	upgradeTimer += deltatime;
	if (upgradeTimer > randomUpgradeTime) {
		int randomType = rand() % 4;
		std::cout << randomType << std::endl;
		if (randomType == 3) {
			randomType = 0;
			std::cout << randomType << std::endl;

		}

		Vector2 randomPos = Vector2(rand() % 550, rand() % 260 + 400);
		addUpgrade(Upgrades(randomType), randomPos);

		randomUpgradeTime = rand() % 5 + 4;
	
		upgradeTimer = 0;
	}
}

void MyScene::grabUpgrade()
{
	std::vector<Upgrade_Base*>::iterator it = upgradeVector.begin();
	while (it != upgradeVector.end()) {
		if (player->isColliding((*it))) {
			//using the upgrade
			(*it)->use(player);
			(*it)->pos = Vector2(-100, -100);

			//removing the upgrade after being used
			if ((*it)->used) {
				Upgrade_Base* u = (*it);
				it = upgradeVector.erase(it);
				this->removechild(u);
			}
		}
		else {
			it++;
		}
	}
}

void MyScene::deleteBullets() {

	//delete player bullets
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end()) {
		if ((*it)->isOutOfCanvas()) {
			Bullet* u = (*it);
			it = bulletVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
}

void MyScene::deleteExplosions()
{
	std::vector<Explosion*>::iterator it = explosionVector.begin();
	while (it != explosionVector.end()) {
		if ((*it)->getExplosionDone()) {
			Explosion* u = (*it);
			it = explosionVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
}

void MyScene::buildPauseMenu()
{
	Button* play = new Button(Button::buttonType::PLAY);
	play->pos = Vector2(200, 50);
	play->size = Vector2(200, 50);
	play->texturePath = "assets/buttons/playButton.png";
	pauseMenuVector.push_back(play);
	addchild(play);

	Button* options = new Button(Button::buttonType::OPTIONS);
	options->pos = Vector2(200, 150);
	options->size = Vector2(200, 50);
	options->texturePath = "assets/buttons/optionsButton.png";
	pauseMenuVector.push_back(options);
	addchild(options);

	Button* quit = new Button(Button::buttonType::QUIT);
	quit->pos = Vector2(200, 250);
	quit->size = Vector2(200, 50);
	quit->texturePath = "assets/buttons/quitButton.png";
	pauseMenuVector.push_back(quit);
	addchild(quit);
}

void MyScene::destroyPauseMenu()
{
	std::vector<Entity*>::iterator it = pauseMenuVector.begin();
	while (it != pauseMenuVector.end()) {
		Entity* u = (*it);
		it = pauseMenuVector.erase(it);
		this->removechild(u);
	}

	pauseMenuVector.clear();
}

void MyScene::updatePauseMenu()
{
	std::vector<Entity*>::iterator it = pauseMenuVector.begin();
	while (it != pauseMenuVector.end()) {
		Button* button = (Button*)(*it);
		if (button->isClicked()) {
			if (button->getType() == Button::buttonType::PLAY) {
				paused = false;
				pausedMenuUp = true;
			}

			if (button->getType() == Button::buttonType::OPTIONS) {
				SceneManager::getInstance()->setCurrentScene("OptionsScene");
				SceneManager::getInstance()->sceneVector["OptionsScene"]->lastScene = "MyScene";
			}

			if (button->getType() == Button::buttonType::QUIT) {
				SceneManager::getInstance()->setCurrentScene("MenuScene");
			}
			break;
		}
		else {
			it++;
		}
	}
}

void MyScene::enemyShoot() {
	std::vector<IEnemy*>::iterator it = enemyVector.begin();
	while (it != enemyVector.end()) {
		if ((*it)->canShoot) {
			if ((*it)->type == IEnemy::FAST || (*it)->type == IEnemy::BASIC) {
				(*it)->canShoot = false;
				Bullet* bullet;

				if ((*it)->type == IEnemy::FAST) {
					bullet = new Bullet("assets/bullet_concept2.png", (*it));
					bullet->size = Vector2(25, 25);
					bullet->setSpeed(25);
				}
				else if ((*it)->type == IEnemy::BASIC) {
					bullet = new Bullet();
					bullet->setOrigin((*it));
				}

				bullet->playerBullet = false;
				bullet->pos = (*it)->pos;
				bullet->pos.y = (*it)->pos.y + (*it)->size.y / 2 + 30;
				bullet->pos.x = (*it)->pos.x + (*it)->size.y / 2 - 5;

				bullet->direction = Vector2(0, player->getBulletSpeed());

				bulletVector.push_back(bullet);
				addchild(bullet);
			}
			else if ((*it)->type == IEnemy::BOSS) {
				(*it)->canShoot = false;

				EnemyBoss* boss = dynamic_cast<EnemyBoss*> (*it);

				if (boss != NULL) {
					std::vector<Vector2> dirV = boss->getBulletDirection(18);
					std::vector<Vector2>::iterator at = dirV.begin();
					while (at != dirV.end()) {

						Bullet* bullet = new Bullet("assets/bullet_concept2.png", (boss));
						bullet->pos = boss->pos + Vector2(boss->size.x / 2, boss->size.y / 2);
						bullet->size = Vector2(25, 25);
						bullet->setSpeed(70);
						bullet->direction = (*at);

						bulletVector.push_back(bullet);
						addchild(bullet);

						at++;
					}
				}
			}
			Audio::getInstance()->playAudio("pewSound.wav", 0, 2);
		}
		it++;
	}
}

void MyScene::bulletHits()
{
	//player bullet hits enemy
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end()) {
		if ((*it)->getIsDead()) {
			Bullet* u = (*it);
			it = bulletVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
}

void MyScene::deadEnemyCleanup()
{
	std::vector<IEnemy*>::iterator it = enemyVector.begin();
	while (it != enemyVector.end()) {
		if ((*it)->getIsDead() || (*it)->health <= 0) {

			//cleans the bullets up from the boss after he dies.
			EnemyBoss* boss = dynamic_cast<EnemyBoss*>(*it);
			if (boss != NULL) {
				std::vector<Bullet*>::iterator those = bulletVector.begin();
				while (those != bulletVector.end()) {
					Bullet* u = (*those);
					those = bulletVector.erase(those);
					this->removechild(u);
				}
				bulletVector.clear();
			}

			score += (*it)->pointsWorth;

			Explosion* expl = new Explosion((*it)->pos - (*it)->size, (*it)->size * 3.0f);
			explosionVector.push_back(expl);
			addchild(expl);

			IEnemy* u = (*it);
			it = enemyVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
}

void MyScene::playerDie()
{
	if (player->health <= 0) {
		removechild(player);
		paused = true;

		Explosion* expl = new Explosion(player->pos, player->size);
		addchild(expl);
		explosionVector.push_back(expl);
	}
}

void MyScene::addZLayers(int zlayerAmount)
{
	setZLayer(zlayerAmount);

	for (int i = 0; i <= getZlayer() - 1; i++) {
		std::vector<Entity*>zlayer;
		ZLayers.push_back(zlayer);
	}
}

void MyScene::levelBuilder()
{
	switch (level)
	{
	case 1:
		for (int i = 0; i < 6; i++) {
			addEnemy(IEnemy::BASIC, Vector2(100 * (i + 1), 50));
		}
		for (int i = 0; i < 5; i++) {
			addEnemy(IEnemy::BASIC, Vector2(100 * (i + 1) + 50, 150));
		}
		break;
		
	case 2:
		for (int i = 0; i < 5; i++) {
			addEnemy(IEnemy::BASIC, Vector2(100 * (i + 1) + 50, 50));
		}
		for (int i = 0; i < 4; i++) {
			addEnemy(IEnemy::BASIC, Vector2(100 * (i + 1) + 100, 150));
		}
		addEnemy(IEnemy::FAST, Vector2(660, 300));
		addEnemy(IEnemy::FAST, Vector2(750, 200));
		break;

	case 3:
		addEnemy(IEnemy::BOSS, Vector2(0,0));
		break;

	default:
		break;
	}
}

void MyScene::levelManager()
{
	if (enemyVector.empty()) {
		level++;
		levelBuilder();
		std::vector<IEnemy*>::iterator it = enemyVector.begin();
		while (it != enemyVector.end()) {
			(*it)->health++;
			it++;
		}
	}
	if (level > 3) {
		level = 1;
		wave++;
		levelBuilder();
	}
}
