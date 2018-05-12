#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{
	texturePath = "assets/enemy_concept.png";
	size = Vector2(50, 50);
}

EnemyBasic::~EnemyBasic()
{

}

void EnemyBasic::update(double deltatime)
{
	Entity::update(deltatime);
}

void EnemyBasic::shoot()
{
	//virtual overloader
}
