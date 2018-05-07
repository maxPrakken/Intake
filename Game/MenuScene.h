#pragma once

#include "../MXP3/include/scene.h"

#include "grid.h"
#include "Player.h"
#include "bullet.h"

#include <typeinfo>
#include <iostream>

class MenuScene : public Scene {
public:
	//constructor
	MenuScene();

	//deconstructor
	virtual ~MenuScene();

	//update function
	virtual void update(double deltatime);

private:
	//std::vector<>
};
