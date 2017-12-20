#include "bullet.h"

Bullet::Bullet() 
{
	texturePath = "assets/INA.png";
	size = Vector2(50, 25);
	speed = 1000;

	direction = Vector2(0, 0);
}

Bullet::~Bullet()
{

}

void Bullet::update(double deltatime)
{
	Entity::update(deltatime);

	pos += direction * speed * deltatime;
}
