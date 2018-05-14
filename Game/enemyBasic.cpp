#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{
	texturePath = "assets/enemy_concept.png";
	size = Vector2(50, 50);

	Vector2 pos1 = Vector2(100, 100);
	Vector2 pos2 = Vector2(200, 200);
	Vector2 pos3 = Vector2(300, 100);

	//sacraficial position, i dont know why but for some reason it doesn't go
	//to the last pos in the list, so this is a simple and dirty fix
	Vector2 sacraficialpos = Vector2(0, 0);

	pointVector.push_back(pos1);
	pointVector.push_back(pos2);
	pointVector.push_back(pos3);

	pointVector.push_back(sacraficialpos);
	
}

EnemyBasic::~EnemyBasic()
{

}

void EnemyBasic::update(double deltatime)
{
	IEnemy::update(deltatime);

	shootTimer += deltatime;
	shoot();
}

void EnemyBasic::shoot()
{
	if (shootTimer > randomMaxTimer) {
		canShoot = true;
		shootTimer = 0;
		randomMaxTimer = rand() % 3;
	}
}
