#pragma once

#include "entity.h"
#include "renderer.h"

class __declspec(dllexport) Agent : public Entity {
public:
	//default constructor
	Agent() { health = 0; }
	//deconstructor
	virtual ~Agent() {}
	//update function
	virtual void update(double deltatime) { Entity::update(deltatime); }

	//int health
	int health;

private:

};