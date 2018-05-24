#include "EnemyFast.h"

EnemyFast::EnemyFast()
{
	texturePath = "assets/enemy_2_Concept.png";
	size = Vector2(50, 50);
	setHealth(1);
	type = IEnemy::FAST;
}

EnemyFast::EnemyFast(Vector2 position)
{
	size = Vector2(50, 50);
	pos = position;
	startPosition = pos;
	this->type = type;

	type = IEnemy::FAST;

	spitesheetPath = "assets/spritesheets/enemy_2_Concept_spritesheet.png";
	animator.rows = Vector2(4, 1);
	animator.paused = true;
	animator.cur = 0;
	animator.animateFromTo = Vector2(1, 3);
	animator.switchAfter = 0.1f;

	pointsWorth = 150;
	setHealth(1);
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

	if (getIsDead()) {
		animator.paused = false;
		if (animator.cur == animator.rows.x - 1) {
			animator.paused = true;
			setDelete(true);
		}
	}
}

void EnemyFast::shoot()
{
	if (shootTimer > randomMaxTimer) {
		canShoot = true;
		shootTimer = 0;
		randomMaxTimer = rand() % 3;
	}
}
