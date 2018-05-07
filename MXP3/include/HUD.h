#pragma once

#include "entity.h"

class HUD : public Entity {
public:
	//default constructor
	HUD();
	
	//default deconstructor
	virtual ~HUD();

	//update function
	virtual void update(double deltatime);

	std::vector<Entity*>HUDElements;

private:

};