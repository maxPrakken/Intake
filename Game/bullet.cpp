#include "bullet.h"

Bullet::Bullet() 
{
	texturePath = "assets/bullet_concept.png";
	size = Vector2(10, 4);
	speed = 100;

	direction = Vector2(0, 0);
}

Bullet::~Bullet()
{

}

void Bullet::update(double deltatime)
{
	Entity::update(deltatime);

	if (playerBullet) {
		pos += direction * speed * deltatime;
	}
	else {
		pos -= direction * speed * deltatime;

	}
}
