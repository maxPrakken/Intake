#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(8, 8), "assets/background_space_tiles_v6.png", Vector2(100, 100), true, Vector2(10, 1));
	background->pos = Vector2(-100, 0);
	addchild(background);

	player = new Player();
	player->size = Vector2(50, 50);
	addchild(player);
}

MyScene::~MyScene()
{

}

void MyScene::update(double deltatime)
{
	Scene::update(deltatime);

	if (player->hasShot) {
		playerShoot();
	}

	addBulletsToScene();
}

void MyScene::addBulletsToScene()
{
	std::vector<Bullet*> bulletVectorCopy = player->getBullets();
	std::vector<Bullet*>::iterator it = bulletVectorCopy.begin();
	while (it != bulletVectorCopy.end()) {
		if(&(*it)->getParent() == NULL) {
			addchild((*it));
		}

		it++;
	}
}

void MyScene::playerShoot()
{
	//bullets shoot in the wrong direction, and are not normalised yet.

	std::vector<Bullet*> bulletVectorCopy = player->getBullets();

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

	bulletVectorCopy.push_back(bullet);
	bulletVectorCopy.push_back(bullet2);

	addchild(bullet);
	addchild(bullet2);

	player->hasShot = false;
}
