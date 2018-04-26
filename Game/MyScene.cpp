#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	addUpgrade(HEALTH, Vector2(100, 100));

	player = new Player();
	player->size = Vector2(50, 50);
	addchild(player);
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

	addBulletsToScene();
	grabUpgrade();
}

void MyScene::addBulletsToScene()
{
	std::vector<Bullet*>::iterator it = bulletVector.begin();
	while (it != bulletVector.end()) {
		if(&(*it)->getParent() == NULL) {
			addchild((*it));
		}

		it++;
	}
}

void MyScene::playerShoot()
{
	//bullets shoot in the wrong direction, and are not normalised yet.

	Bullet* bullet = new Bullet(); 
	bullet->pos = player->pos;
	bullet->pos.y = player->pos.y - player->size.y / 2 + 30;

	Bullet* bullet2 = new Bullet();
	bullet2->pos = player->pos;
	bullet2->pos.y = player->pos.y - player->size.y / 2 + 30;
	bullet2->pos.x = player->pos.x + player->size.x - 12;

	//TODO: make a bulletspeed function
	bullet->direction = Vector2(0, player->getBulletSpeed());
	bullet->rot = 90;

	bullet2->direction = Vector2(0, -10);
	bullet2->rot = 90;

	bulletVector.push_back(bullet);
	bulletVector.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

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

			std::cout << player->health << std::endl;

			//using the upgrade
			(*it)->use(player);
			
			//removing the upgrade after being used
			Upgrade_Base* u = (*it);
			it = upgradeVector.erase(it);
			this->removechild(u);

			std::cout << player->health << std::endl;

		}
		else {
			it++;
		}
	}
}

void MyScene::deleteBullets() {

}

