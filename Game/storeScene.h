#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Button.h"
#include "MyScene.h"
#include "HighScoreMenu.h"

#include <typeinfo>
#include <iostream>

class StoryScene : public Scene {
public:
	//default constructor
	StoryScene();
	//default deconstructor
	virtual ~StoryScene();
	//update function
	virtual void update(double deltatime);
private:
	int getSBAmount();
}
