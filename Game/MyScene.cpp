#include "MyScene.h"

MyScene::MyScene() : Scene()
{
	background = new Grid(Vector2(12, 8), "assets/test.png", Vector2(100, 100));
	background->pos = Vector2(-100, 0);
	addchild(background);

	platformSpawn(Vector2(100, 400));
	platformSpawn(Vector2(350, 400));

	player = new Player();
	player->size = Vector2(100, 100);
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

	EntitiesGrounded();
	addBulletsToScene();
}

void MyScene::EntitiesGrounded()
{
	
	std::vector<Entity*>::iterator it = platformVector.begin();
	while (it != platformVector.end()) {
		if (player->isColliding((*it)) && player->pos.y < (*it)->pos.y - 90 && player->velocity.y >= 0) {
			player->velocity = Vector2(0, 0);
			player->grounded = true;
			break;
		}
		else if (!player->isColliding((*it))) {
			player->grounded = false;
		}

		it++;
	}
}

void MyScene::platformSpawn(Vector2 position)
{
	Entity* platform = new Entity();
	Entity* platform2 = new Entity();

	platform->texturePath = "assets/cobblestone.png";
	platform2->texturePath = "assets/cobblestone.png";

	platform->size = Vector2(100, 100);
	platform2->size = Vector2(100, 100);

	platform->pos = position;
	platform2->pos = Vector2(platform->pos.x + platform->size.x + 50, platform->pos.y);

	platformVector.push_back(platform);
	platformVector.push_back(platform2);

	addchild(platform);
	addchild(platform2);
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
	bullet->texturePath = "assets/INA.png";
	bullet->pos = player->pos;

	Vector2 dir = player->pos - Input::getInstance()->getMouseToScreen();
	dir.normalize();
	bullet->direction = dir * -1.0f;

	bullet->rot = player->pos.angleRelTo(Input::getInstance()->getMouseToScreen());

	bulletVectorCopy.push_back(bullet);

	addchild(bullet);

	player->hasShot = false;
}
