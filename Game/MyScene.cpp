#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	addUpgrade(DOUBLESHOT, Vector2(100, 200));
	addUpgrade(RPM, Vector2(200, 200));
	addUpgrade(HEALTH, Vector2(300, 200));

	player = new Player();
	addchild(player);

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

	//clears enemyBulletVector
	std::vector<Bullet*>::iterator those3 = enemyBulletVector.begin();
	while (those3 != enemyBulletVector.end()) {
		Bullet* u = (*those3);
		those3 = enemyBulletVector.erase(those3);
		this->removechild(u);
	}
	enemyBulletVector.clear();

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
	if (!paused) {
		Scene::update(deltatime);

		if (pausedMenuUp)
			destroyPauseMenu();

		pausedMenuUp = false;
	}
	else {
		buildPauseMenu();
		updatePauseMenu();
	}

	//pauses the entire scene, nothing gets updated
	if (Input::getInstance()->getKeyDown(SDLK_ESCAPE)) {
		if (paused) {
			paused = false;
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

	addStartEnemies();
	
	paused = false;
	pausedMenuUp = true;

	wave = 0;
	score = 0;
}

void MyScene::playerShoot()
{
	Bullet* bullet = new Bullet();
	bullet->pos = player->pos;
	bullet->pos.y = player->pos.y - player->size.y / 2 + 30;

	Bullet* bullet2 = new Bullet();
	bullet2->pos = player->pos;
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 32;
	bullet2->pos.x = player->pos.x + player->size.x - 12;

	bullet->direction = Vector2(0, player->getBulletSpeed());
	bullet->rot = 90;

	bullet2->direction = Vector2(0, -10);
	bullet2->rot = 90;

	bulletVector.push_back(bullet);
	bulletVector.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

	if (player->doubleShot) {
		Bullet* bullet3 = new Bullet();
		bullet3->pos = player->pos;
		bullet3->pos.x = player->pos.x + 10;
		bullet3->pos.y = player->pos.y - player->size.y / 2 + 31;

		Bullet* bullet4 = new Bullet();
		bullet4->pos = player->pos;
		bullet4->pos.y = player->pos.y - player->size.y / 2 + 34;
		bullet4->pos.x = player->pos.x + player->size.x - 22;

		bullet3->direction = Vector2(0, player->getBulletSpeed());
		bullet3->rot = 90;

		bullet4->direction = Vector2(0, -10);
		bullet4->rot = 90;

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
			EnemyBasic* enemy = new EnemyBasic(position, IEnemy::BASIC);
			addchild(enemy);
			enemyVector.push_back(enemy);
			break;
		}

		case IEnemy::FAST:
		{
			EnemyBasic* enemy = new EnemyBasic(position, IEnemy::FAST);
			enemyVector.push_back(enemy);
			addchild(enemy);
			break;
		}

		case IEnemy::BOSS:
		{
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
	addEnemy(IEnemy::BASIC, Vector2(200, 50));
	//addEnemy(IEnemy::BASIC, Vector2(280, 50));
	//addEnemy(IEnemy::BASIC, Vector2(360, 50));
	addEnemy(IEnemy::FAST, Vector2(440, 50));
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
		if ((*it)->pos.y < -50) {
			Bullet* u = (*it);
			it = bulletVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
	
	//delete enemy bullets
	std::vector<Bullet*>::iterator Eit = enemyBulletVector.begin();
	while (Eit != enemyBulletVector.end()) {
		if ((*Eit)->pos.y > Renderer::getInstance()->getResolution().y + 10) {
			Bullet* u = (*Eit);
			Eit = enemyBulletVector.erase(Eit);
			this->removechild(u);
		}
		else {
			Eit++;
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

	pausedMenuUp = true;
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
			std::cout << button->getType() << std::endl;
			if (button->getType() == Button::buttonType::PLAY) {
				paused = false;
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
			(*it)->canShoot = false;
			Bullet* bullet = new Bullet();
			bullet->playerBullet = false;
			bullet->pos = (*it)->pos;
			bullet->pos.y = (*it)->pos.y + (*it)->size.y / 2 + 30;
			bullet->pos.x = (*it)->pos.x + (*it)->size.y / 2 - 5;

			bullet->direction = Vector2(0, player->getBulletSpeed());
			bullet->rot = 90;

			enemyBulletVector.push_back(bullet);
			addchild(bullet);
		}
		it++;
	}
}

void MyScene::bulletHits()
{
	//player bullet hits enemy
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	std::vector<IEnemy*>::iterator enemy = enemyVector.begin();
	while (it != bulletVector.end()) {
		while (enemy != enemyVector.end()) {
			if ((*it)->isColliding((*enemy))) {
				Bullet* u = (*it);
				it = bulletVector.erase(it);
				this->removechild(u);

    			(*enemy)->setHealth((*enemy)->getHealth() - 1);
			}
			enemy++;			
		}
		it++;
	}
	
	//enemy bullet hits player
	std::vector<Bullet*>::iterator Eit = enemyBulletVector.begin();
	while (Eit != enemyBulletVector.end()) {
		if ((*Eit)->isColliding(player)) {
			Bullet* u = (*Eit);
			Eit = enemyBulletVector.erase(Eit);
			this->removechild(u);

			player->health--;
		}
		else {
			Eit++;
		}
	}
}

void MyScene::deadEnemyCleanup()
{
	std::vector<IEnemy*>::iterator it = enemyVector.begin();
	while (it != enemyVector.end()) {
		if ((*it)->getDelete()) {
			IEnemy* u = (*it);
			it = enemyVector.erase(it);
			this->removechild(u);
		}
		else {
			it++;
		}
	}
}
