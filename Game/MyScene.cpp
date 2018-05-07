#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	addUpgrade(DOUBLESHOT, Vector2(100, 200));
	addUpgrade(RPM, Vector2(200, 200));

	player = new Player();
	addchild(player);

	button = new Button();
	addchild(button);
}

MyScene::~MyScene()
{
	for (unsigned int i = 0; i < upgradeVector.size(); i++) {
		removechild(upgradeVector[i]);
		delete upgradeVector[i];
	}
	upgradeVector.clear();

	delete background;
	delete player;
}

void MyScene::update(double deltatime)
{
	Scene::update(deltatime);

	if (player->hasShot) {
		playerShoot();
	}

	grabUpgrade();
	deleteBullets();
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
	switch(upgrade) 
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

