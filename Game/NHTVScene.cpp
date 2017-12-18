#include "NHTVScene.h"

NHTVScene::NHTVScene() : Scene()
{
	
	background = new Grid(Vector2(12, 8), "assets/test.png", Vector2(100, 100));
	background->pos = Vector2(-100, 0);
	addchild(background);

	platformSpawn(Vector2(100, 400));

	player = new NHTVPlayer();
	player->size = Vector2(100, 100);
	addchild(player);
}

NHTVScene::~NHTVScene()
{

}

void NHTVScene::update(double deltatime)
{
	Scene::update(deltatime);

	//std::cout << player->velocity.y << std::endl;

	EntitiesGrounded();
	addBulletsToScene();
}

void NHTVScene::EntitiesGrounded()
{
	std::vector<Entity*>::iterator it = platformVector.begin();
	while (it != platformVector.end()) {
		if (player->isColliding((*it)) && player->pos.y < (*it)->pos.y - 90 && player->velocity.y >= 0) {
			player->velocity = Vector2(0, 0);
			player->grounded = true;
		}
		else
		player->grounded = false;
		it++;
	}
}

void NHTVScene::platformSpawn(Vector2 position)
{
	Entity* platform = new Entity();
	Entity* platform2 = new Entity();

	platform->texturePath = "assets/cobblestone.png";
	platform2->texturePath = "assets/cobblestone.png";

	platform->size = Vector2(100, 100);
	platform2->size = Vector2(100, 100);

	platform->pos = position;
	platform2->pos = Vector2(platform->pos.x + platform->size.x, platform->pos.y);

	platformVector.push_back(platform);
	//platformVector.push_back(platform2);

	addchild(platform);
	//addchild(platform2);
}

void NHTVScene::addBulletsToScene()
{
	std::vector<Bullet*> bulletVectorCopy = player->getBullets();
	std::vector<Bullet*>::iterator it = bulletVectorCopy.begin();
	while (it != bulletVectorCopy.end()) {
		if(&(*it)->getParent() == NULL) {
			addchild((*it));
		}
		player->bulletRotDir((*it));

		it++;
	}
}
