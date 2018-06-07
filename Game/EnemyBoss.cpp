#include "EnemyBoss.h"
#include <input.h>
EnemyBoss::EnemyBoss()
{
	texturePath = "assets/eindbaas_concept.png";
	size = Vector2(100, 100);
	pos = Vector2((Renderer::getInstance()->getResolution().x / 2) - (this->size.x / 2), (Renderer::getInstance()->getResolution().y / 2) - (this->size.x / 2));
	health = 10;
	type = IEnemy::BOSS;
	pointsWorth = 1000;
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::update(double deltatime)
{
	Entity::update(deltatime);

	if (this->isColliding(Input::getInstance()->getMouseToScreen())) {
		std::cout << test << std::endl;
		test++;
	}
}

void EnemyBoss::shoot()
{

}
