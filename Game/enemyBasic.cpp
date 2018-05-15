#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{
	texturePath = "assets/enemy_concept.png";
	size = Vector2(50, 50);
	setHealth(2);
}

EnemyBasic::EnemyBasic(Vector2 position, IEnemy::enemyTypes type)
{
	size = Vector2(50, 50);
	pos = position;
	startPosition = pos;
	
	if (type == IEnemy::enemyTypes::BASIC) {
		texturePath = "assets/enemy_concept.png";

		Vector2 pos1 = startPosition;
		Vector2 pos2 = Vector2(startPosition.x - 50, startPosition.y + 50);
		Vector2 pos3 = Vector2(pos2.x - 50, pos2.y - 50);

		//sacraficial position, i dont know why but for some reason it doesn't go
		//to the last pos in the list, so this is a simple and dirty fix
		Vector2 sacraficialpos = Vector2(0, 0);

		pointVector.push_back(pos1);
		pointVector.push_back(pos2);
		pointVector.push_back(pos3);
		pointVector.push_back(sacraficialpos);
	}

	else if (type == IEnemy::enemyTypes::FAST) {
		texturePath = "assets/enemy_2_concept.png";
		setSpeed(getSpeed() * 1.5);

		Vector2 pos1 = Vector2(-50, position.y);
		Vector2 pos2 = Vector2(Renderer::getInstance()->getResolution().x, position.y);
		Vector2 pos3 = Vector2(Renderer::getInstance()->getResolution().x, position.y + 200);
		Vector2 pos4 = Vector2(-50, position.y + 200);

		//sacraficial position, i dont know why but for some reason it doesn't go
		//to the last pos in the list, so this is a simple and dirty fix
		Vector2 sacraficialpos = Vector2(0, 0);

		pointVector.push_back(pos1);
		pointVector.push_back(pos2);
		pointVector.push_back(pos3);
		pointVector.push_back(pos4);
		pointVector.push_back(sacraficialpos);
	}
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
