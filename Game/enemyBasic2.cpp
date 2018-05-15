#include "EnemyBasic2.h"

EnemyBasic2::EnemyBasic2()
{
	texturePath = "assets/enemy_concept.png";
	size = Vector2(50, 50);
	setHealth(2);
}

EnemyBasic2::EnemyBasic2(Vector2 position)
{
}

EnemyBasic2::~EnemyBasic2()
{

}

void EnemyBasic2::update(double deltatime)
{
	Entity::update(deltatime);

}

void EnemyBasic2::shoot()
{
	//virtual overloader
}
