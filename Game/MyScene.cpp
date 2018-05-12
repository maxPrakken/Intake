#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	addUpgrade(DOUBLESHOT, Vector2(100, 200));
	addUpgrade(RPM, Vector2(200, 200));

	addStartEnemies();

	player = new Player();
	addchild(player);

	paused = false;
	pausedMenuUp = false;

	wave = 0;
	score = 0;
}

MyScene::~MyScene()
{
	std::vector<Upgrade_Base*>::iterator it = upgradeVector.begin();
	while (it != upgradeVector.end()) {
		Upgrade_Base* u = (*it);
		it = upgradeVector.erase(it);
		this->removechild(u);
	}
	upgradeVector.clear();

	std::vector<Entity*>::iterator that = pauseMenuVector.begin();
	while (that != pauseMenuVector.end()) {
		Entity* u = (*that);
		that = pauseMenuVector.erase(that);
		this->removechild(u);
	}
	pauseMenuVector.clear();

	std::vector<Bullet*>::iterator those = bulletVector.begin();
	while (those != bulletVector.end()) {
		Bullet* u = (*those);
		those = bulletVector.erase(those);
		this->removechild(u);
	}
	bulletVector.clear();

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
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 30;
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
		bullet3->pos.y = player->pos.y - player->size.y / 2 + 30;

		Bullet* bullet4 = new Bullet();
		bullet4->pos = player->pos;
		bullet4->pos.y = player->pos.y - player->size.y / 2 + 30;
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
			EnemyBasic* enemy = new EnemyBasic();
			enemy->pos = position;
			addchild(enemy);
			enemyVector.push_back(enemy);
			break;
		}

		case IEnemy::BASIC2:
		{
			EnemyBasic2* enemy = new EnemyBasic2();
			enemy->pos = position;
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
	addEnemy(IEnemy::BASIC, Vector2(50, 50));
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
				//TODO: do something with a reset here, because it doesnt stop
				//the scene just switches
			}
			break;
		}
		else {
			it++;
		}
	}
}

