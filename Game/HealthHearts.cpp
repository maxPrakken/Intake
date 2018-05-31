#include "HealthHearts.h"

HealthHearts::HealthHearts()
{
	
}

HealthHearts::HealthHearts(Player * p)
{
	if (p != NULL) {
		player = p;

		for (int i = 0; i < player->health; i++) {
			addHeart();
		}
	}
}

HealthHearts::~HealthHearts()
{
	//clears upgradeVector
	std::vector<Entity*>::iterator it = heartVector.begin();
	while (it != heartVector.end()) {
		Entity* u = (*it);
		it = heartVector.erase(it);
		this->removechild(u);
	}
	heartVector.clear();
}

void HealthHearts::update(double deltatime)
{
	Entity::update(deltatime);

	manageHearts();
}

void HealthHearts::manageHearts()
{
	if (player->health != heartVector.size()) {
		if (player->health < heartVector.size()) {
			removeLastHeart();
		}
		else {
			addHeart();
		}
	}
}

void HealthHearts::addHeart()
{
	Entity* heart = new Entity();
	heart->texturePath = "assets/heart.png";
	heart->size = Vector2(50, 50);
	addchild(heart);
	heartVector.push_back(heart);

	if (heartVector.empty()) {
		heart->pos = Vector2(0, 0);
	}
	else {
		heart->pos = Vector2(0, heart->size.y * (heartVector.size() - 1));
	}
}

void HealthHearts::removeLastHeart()
{
	std::vector<Entity*>::iterator it = heartVector.begin();
	while (it != heartVector.end()) {
		it++;
		
	} 
	it--;
	Entity* u = (*it);
	it = heartVector.erase(it);
	this->removechild(u);
}
