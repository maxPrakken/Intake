#pragma once 

#include "../MXP3/include/entity.h"

#include "Player.h"

class HealthHearts : public Entity {
public: 

	//default constructor
	HealthHearts();
	//constructor overloader to get current health on player
	HealthHearts(Player* p);
	//default deconstructor
	virtual ~HealthHearts();
	//update class
	virtual void update(double deltatime);
private:
	//keeps track of hearts in update
	void manageHearts();

	//add hearts
	void addHeart();

	//removes last heart that was added
	void removeLastHeart();

	//player pointer
	Player* player;

	//holds hearts
	std::vector<Entity*>heartVector;
};