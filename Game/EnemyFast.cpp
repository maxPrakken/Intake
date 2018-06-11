#include "EnemyFast.h"

EnemyFast::EnemyFast()
{
	texturePath = "assets/enemy_2_Concept.png";
	size = Vector2(50, 50);
	health = 1;
	type = IEnemy::FAST;
}

EnemyFast::EnemyFast(Vector2 position)
{
	size = Vector2(50, 50);
	pos = position;
	startPosition = pos;
	type = IEnemy::FAST;
	setGoCircles(true, 360, 0.02);

	texturePath = "assets/enemy_2_Concept.png";	animator.rows = Vector2(4, 1);

	pointsWorth = 150;
	health = 1;
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

EnemyFast::~EnemyFast()
{
	std::vector<Vector2>::iterator it = pointVector.begin();
	while (it != pointVector.end()) {
		Vector2 u = (*it);
		it = pointVector.erase(it);
	}
	pointVector.clear();
}

void EnemyFast::update(double deltatime)
{
	IEnemy::update(deltatime);

	shootTimer += deltatime;
	shoot();
}

void EnemyFast::shoot()
{
	if (shootTimer > randomMaxTimer) {
		canShoot = true;
		shootTimer = 0;
		randomMaxTimer = rand() % 3 + 1;
	}
}
