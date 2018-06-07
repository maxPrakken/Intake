#include "Bullet.h"

Bullet::Bullet() 
{
	texturePath = "assets/bullet_concept.png";
	size = Vector2(4, 10);
	speed = 50;
	damage = 1;

	direction = Vector2(0, 0);
}

Bullet::Bullet(std::string texturepath)
{
	this->texturePath = texturepath;
	size = Vector2(10, 4);
	speed = 10;
	damage = 1;

	direction = Vector2(0, 0);
}

Bullet::Bullet(std::string texturepath, Entity* origin)
{
	this->texturePath = texturepath;
	size = Vector2(10, 4);
	speed = 10;
	damage = 1;
	this->origin = origin;

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

	hit();
}

void Bullet::hit()
{
	std::vector<std::vector<Entity*>>::iterator it = getParentPointer()->ZLayers.begin();
	while (it != getParentPointer()->ZLayers.end())
	{
		std::vector<Entity*>::iterator at = (*it).begin();
		while (at != (*it).end()) {
			Agent* agent = dynamic_cast<Agent*> (*at);

			if (agent != NULL) {
				if (agent->isColliding(this->pos) && agent != origin) {
					agent->health -= damage;
					damage = 0;
					isDead = true;
					return;
				}
				else {
					at++;
				}
			}
			else {
				at++;
			}
		}
		it++;
	}
}
