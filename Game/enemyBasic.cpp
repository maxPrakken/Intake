#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{
	this->texturePath = "assets/INA.png";
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
