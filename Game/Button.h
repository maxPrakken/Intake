#pragma once

#include "entity.h"
#include "input.h"

class Button : public Entity {
public:
	//constructor
	Button();

	//deconstructor
	virtual ~Button();

	//update function
	virtual void update(double deltatime);

	bool isClicked();

private:
	
};
