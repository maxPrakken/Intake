#pragma once

#include "../MXP3/include/scene.h"

#include <sceneManager.h>

#include "grid.h"
#include "Player.h"
#include "bullet.h"
#include "Button.h"

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
	Button* playButton;
	Button* optionsButton;
	Button* highscoresButton;
	Button* quitButton;

	std::vector<Button*>buttonVector;
};
