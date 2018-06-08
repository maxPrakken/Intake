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
	//circleSpeed = 0.1f;

	RPM = 60;
	RPMTimer = 0;
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::update(double deltatime)
{
	Entity::update(deltatime);

	RPMTimer += deltatime;

	shoot();
}

void EnemyBoss::shoot()
{
	double xValue = RPM / 60;
	double fireTime = 1 / xValue;
	if (RPMTimer > fireTime) {
		canShoot = true;

		RPMTimer = 0;
	}
}

std::vector<Vector2> EnemyBoss::getBulletDirection(int bulletamount)
{
	float spacing = 360 / bulletamount;
	float SAngle = circleAngle + spacing;
	float r = 1;

	std::vector<Vector2> vVector;  

	for (int i = 0; i < bulletamount; i++) {
		float posX = (cos(SAngle * i) * r) + (this->pos.x - r);
		float posY = (sin(SAngle * i) * r) + this->pos.y - r;

		Vector2 target = Vector2(posX, posY);
		Vector2 direction = target - this->pos;
		direction.normalize();

		vVector.push_back(direction);
	}
	
	circleAngle += circleSpeed;

	std::vector<Vector2> it = vVector;
	vVector.clear();

	return it;
}
