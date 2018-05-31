#include "Bullet.h"

Bullet::Bullet() 
{
	texturePath = "assets/bullet_concept.png";
	size = Vector2(10, 4);
	speed = 100;
	damage = 1;

	direction = Vector2(0, 0);
}

Bullet::Bullet(std::string texturepath)
{
	this->texturePath = texturepath;
	size = Vector2(10, 4);
	speed = 100;
	damage = 1;

	direction = Vector2(0, 0);
}

Bullet::Bullet(std::string texturepath, Entity* origin)
{
	this->texturePath = texturepath;
	size = Vector2(10, 4);
	speed = 100;
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
	for (int i = 0; i < getParentPointer()->childrenVec.size(); i++) {
		try {
				//checks if the entity we're gonna try to collide with is a agent
				Agent* agent = dynamic_cast<Agent*> (getParentPointer()->childrenVec[i]);

				if(agent != NULL) { 
					if (this->isColliding(agent) && agent != origin) {
						agent->health -= damage;
					}
					else {
						i++;
					}
				}
		}
		catch (...) {
			i++;
		}
	}
}
