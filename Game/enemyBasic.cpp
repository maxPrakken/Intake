#include "EnemyBasic.h"

EnemyBasic::EnemyBasic()
{
	texturePath = "assets/enemy_concept.png";
	size = Vector2(50, 50);
	health = 2;
	type = IEnemy::BASIC;
}

EnemyBasic::EnemyBasic(Vector2 position)
{
	size = Vector2(50, 50);
	pos = position;
	startPosition = pos;
	type = IEnemy::BASIC;
	setGoCircles(true, 50, 0.1);
	
	texturePath = "assets/enemy_concept.png";

	pointsWorth = 100;
	health = 20;

	Vector2 pos1 = startPosition;
	Vector2 pos2 = Vector2(startPosition.x - 50, startPosition.y + 50);
	Vector2 pos3 = Vector2(pos2.x - 50, pos2.y - 50);

	//sacraficial position, i dont know why but for some reason it doesn't go
	//to the last pos in the list, so this is a simple and dirty fix
	Vector2 sacraficialpos = Vector2(0, 0);

	//pointVector.push_back(pos1);
	//pointVector.push_back(pos2);
	//pointVector.push_back(pos3);
	//pointVector.push_back(sacraficialpos);
}

EnemyBasic::~EnemyBasic()
{
	std::vector<Vector2>::iterator it = pointVector.begin();
	while (it != pointVector.end()) {
		Vector2 u = (*it);
		it = pointVector.erase(it);
	}
	pointVector.clear();
}

void EnemyBasic::update(double deltatime)
{
	IEnemy::update(deltatime);
	std::cout << health << std::endl;
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
