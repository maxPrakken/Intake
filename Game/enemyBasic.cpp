#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{

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
